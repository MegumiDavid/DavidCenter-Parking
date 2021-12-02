import { Ticket, Pagamento, Vaga } from './database.js'
import { preco } from './router.js'

export function getPrice(ticket) {
  const start = ticket.horaEntrada
  const end = new Date()
  var diff = Math.abs(end - start)
  diff = diff / 60000
  var taxa = 0

  if (diff < 60) {
    taxa = preco.preco1
  } else if (diff >= 60 && diff < 120) {
    taxa = preco.preco2
  } else if (diff >= 120) {
    taxa = preco.preco3
  }

  console.log(preco)
  return taxa
}

export async function makePayment(ticketcod) {
  const ticket = await Ticket.find(ticketcod)
  switch (ticket.statusSaida) {
    case 'DENIED':
      const price = getPrice(ticket)
      await Pagamento.create({ hora: new Date(), preco: price, codigoTicket: ticketcod })
      await Ticket.save({ codigo: ticketcod, statusSaida: 'OK' })
      console.log('Pagamento realizado com sucesso.')
      break
    case 'OK':
      console.log('Pagamento ja realizado previamente.')
      break
  }
}
