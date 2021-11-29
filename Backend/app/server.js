import Koa from 'koa'
import views from 'koa-views'
import serve from 'koa-static'
import bodyParser from 'koa-bodyparser'

import router from './router.js'

const server = {
  start() {
    const port = process.env.PORT
    const app = new Koa()

    app.use(bodyParser())
    app.use(serve('app/resources/public'))
    app.use(
      views('app/resources/views', {
        extension: 'ejs'
      })
    )
    app.use(router.routes()).use(router.allowedMethods())

    app.listen(port, () => {
      console.log('Servidor iniciado na porta ' + port)
    })
  }
}

export default server
