import Router from '@koa/router'

const router = new Router()

router.get('/', ctx => {
  ctx.body = 'teste'
})

export default router
