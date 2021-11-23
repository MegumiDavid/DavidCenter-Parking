import Router from '@koa/router'
import { Ticket, Pagamento, Vaga } from './database.js'
import makePayment from './payment.js'
import getPrice from './payment.js'

const router = new Router()

router.get('/home', async ctx => {
  const vaga = await Vaga.find('1A01')
  const vagas = await Vaga.all()
  await ctx.render('home', { vagas })
})

router.get('/vagas', async ctx => {
  const vagas = await Vaga.all()

  let vagaLivre = 0
  let vagaOcupada = 0
  let numVagasAndar = []
  let melhorVaga = 0
  let vagaLivre1 = 0
  let vagaLivre2 = 0
  let vagaLivre3 = 0
  let vagaLivre4 = 0
  let vagaLivre5 = 0

  for(let i=0;i<vagas.length;i++)
  {
    if(vagas[i].status == 0)
    {
      vagaLivre++
      switch (Number(vagas[i].codigo[0])) {
        case 1:
          vagaLivre1++
          numVagasAndar[0] = vagaLivre1 
          break;
        case 2:
          vagaLivre2++
          numVagasAndar[1] = vagaLivre2
          break;
        case 3:
          vagaLivre3++
          numVagasAndar[2] = vagaLivre3
          break;
        case 4:
          vagaLivre4++
          numVagasAndar[3] = vagaLivre4
          break;
        case 5:
          vagaLivre5++
          numVagasAndar[4] = vagaLivre5
          break;                  
        default:
          console.log(`O estacionamento não possui o andar ${vagas[i].codigo[0]}`);
      } 
    }
    else{vagaOcupada++}
  }

  function getMaxOfArray(numArray) {
    return Math.max.apply(null, numArray);
  }

  melhorVaga = numVagasAndar.indexOf(getMaxOfArray(numVagasAndar)) + 1
  const statusVaga = `O ${melhorVaga}° andar possui mais vagas disponíveis`
  await ctx.render('vagas', { vagaOcupada , vagaLivre, statusVaga})
})

router.get('/pagamento-online', async ctx => {

})

export default router
