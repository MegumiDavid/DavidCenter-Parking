import Router from '@koa/router'
import { Ticket, Pagamento, Vaga } from './database.js'
import { makePayment, getPrice } from './payment.js'
import { Price } from './precos.js'

const router = new Router()

const preco = new Price(10, 15, 25)
const numVagasAndar = [0,0,0,0,0]

router.get('/', async ctx => {
  await ctx.render('home')
})

router.get('/about-us', async ctx => {
  await ctx.render('about-us')
})

router.get('/pagamento-online', async ctx => {
  await ctx.render('pagamento-online', { preco: preco })
})

router.get('/pagamento-online/cartao', async ctx => {
  await ctx.render('pagamento-online-cartao')
})

router.get('/pagamento-online/pix', async ctx => {
  await ctx.render('pagamento-online-pix')
})

router.post('/pagamento-online/dados', async ctx => {
  const id = ctx.request.body.ticketID
  await ctx.redirect(`/pagamento/${id}`)
})

router.get('/pagamento/:id', async ctx => {
  const id = ctx.params.id
  if (!id) {
    await ctx.render('paymentError', { error: new Error('Código de ticket inválido') })
    return
  }
  const ticket = await Ticket.find(id)
  const price = getPrice(ticket)
  const payments = Pagamento.columnsToData(await Pagamento.query().where({ CODIGO_TICKET_PAG: ticket.codigo }))
  const payment = payments[payments.length - 1] || null

  await ctx.render('payment', { ticket, price, payment })
})

router.post('/pagamento/:id', async ctx => {
  const id = ctx.params.id
  if (!id) {
    await ctx.render('paymentError', { error: new Error('Código de ticket inválido') })
    return
  }

  const data = ctx.request.body

  const ticket = await Ticket.find(id)

  const payments = Pagamento.columnsToData(await Pagamento.query().where({ CODIGO_TICKET_PAG: ticket.codigo }))
  const existingPayment = payments[payments.length - 1] || null
  if (ticket.horaSaida || (existingPayment && existingPayment.validExit())) return ctx.redirect('/pagamento/' + id)

  const price = getPrice(ticket)
  const payment = await makePayment(ticket.codigo)

  await ctx.render('payment', { ticket, price, payment })
})

router.get('/alterar-preco', async ctx => {
  // console.log(`Preço Atual: R$${preco.preco1} R$${preco.preco2} R$${preco.preco3}`);
  await ctx.render('alterar-preco', { preco: preco })
})

router.post('/alterar-preco', async ctx => {
  let preco1 = ctx.request.body.preco1
  let preco2 = ctx.request.body.preco2
  let preco3 = ctx.request.body.preco3

  preco.preco1 = preco1
  preco.preco2 = preco2
  preco.preco3 = preco3

  // console.log(`Preço Modificado: R$${preco.preco1} R$${preco.preco2} R$${preco.preco3}`);
  await ctx.redirect('/alterar-preco')
})

router.get('/vagas', async ctx => {
  const vagas = await Vaga.all()

  let vagaLivre = 0
  let vagaOcupada = 0
  let melhorVaga = 0
  let vagaLivre1 = 0
  let vagaLivre2 = 0
  let vagaLivre3 = 0
  let vagaLivre4 = 0
  let vagaLivre5 = 0
  let statusVaga = ''

  for (let i = 0; i < vagas.length; i++) {
    if (vagas[i].status == 0) {
      vagaLivre++
      switch (Number(vagas[i].codigo[0])) {
        case 1:
          vagaLivre1++
          numVagasAndar[0] = vagaLivre1
          break
        case 2:
          vagaLivre2++
          numVagasAndar[1] = vagaLivre2
          break
        case 3:
          vagaLivre3++
          numVagasAndar[2] = vagaLivre3
          break
        case 4:
          vagaLivre4++
          numVagasAndar[3] = vagaLivre4
          break
        case 5:
          vagaLivre5++
          numVagasAndar[4] = vagaLivre5
          break
        default:
          console.log(`O estacionamento não possui o andar ${vagas[i].codigo[0]}`)
      }
    } else {
      vagaOcupada++
    }
  }

  function getMaxOfArray(numArray) {
    return Math.max.apply(null, numArray)
  }
  function equalValuesTotal(array, num) {
    for (let i = 0; i < array.length; i++) {
      if (array[i] != num) {
        return false
      }
    }
    return true
  }
  function equalValues(array) {
    for (let i = 0; i < array.length; i++) {
      if (array[0] != array[i]) {
        return false
      }
    }
    return true
  }

  let existeEqualValues = equalValues(numVagasAndar)
  let existeEqualValuesTotal = equalValuesTotal(numVagasAndar, 0)

  if (existeEqualValues && existeEqualValuesTotal) {
    // todas as vagas ocupadas
    statusVaga = 'O estacionamento está 100% ocupado'
  } else {
    melhorVaga = numVagasAndar.indexOf(getMaxOfArray(numVagasAndar)) + 1
    statusVaga = `O ${melhorVaga}° andar possui mais vagas disponíveis`
  }
  await ctx.render('vagas', { vagaOcupada, vagaLivre, statusVaga })
})

router.get('/vagas/vagas-andar', async ctx => {
  await ctx.render('vagaPorAndar', { numVagasAndar:numVagasAndar })
})


export { preco }
export default router
