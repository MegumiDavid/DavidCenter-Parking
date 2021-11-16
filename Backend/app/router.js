import Router from '@koa/router'
import { Cliente, Taxa } from './database.js'

const router = new Router()

router.get('/', async ctx => {
  const cliente = await Cliente.create({ statusSaida: 'aaaa' })
  const taxa = await Taxa.create({ codigoTicket: cliente.codigo })
  await ctx.render('home', { cliente, taxa })
})

export default router
