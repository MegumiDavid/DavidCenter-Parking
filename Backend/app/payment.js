import { Ticket, Pagamento, Vaga } from './database.js'

function getPrice(ticket) {
    const start = ticket.horaEntrada;
    const end = new Date();
    var diff = Math.abs(end - start);
    diff = diff/60000;
    var taxa = 0;
    
    if ( diff<60 ){
        taxa = 10;
    } else if ( diff>=60 && diff<120 ) {
        taxa = 15;
    } else if ( diff>=120 ) {
        taxa = 25;
    }
    return taxa;
}

async function makePayment(ticketcod) { 
    const ticket = await Ticket.find(ticketcod);
    const price = getPrice(ticket); 
    await Pagamento.create({ hora: new Date(), preco: price, codigoTicket: ticketcod}); 
    await Ticket.save({codigo: ticketcod, statusSaida: 'OK'});
}

export default makePayment


