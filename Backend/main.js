import dotenv from 'dotenv'
dotenv.config()

import Koa from 'koa'

import database from './app/database.js'
import router from './app/router.js'

const port = process.env.PORT
const app = new Koa()

app.use(router.routes()).use(router.allowedMethods())

app.listen(port, () => {
  console.log('Servidor iniciado na porta ' + port)
})
