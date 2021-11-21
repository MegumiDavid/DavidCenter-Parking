import Router from '@koa/router'
import { Ticket, Pagamento, Vaga } from './database.js'

const router = new Router()

router.get('/home', async ctx => {
  const vaga = await Vaga.find('1A01')
  const vagas = await Vaga.all()
  await ctx.render('home', { vagas })
})

export default router
