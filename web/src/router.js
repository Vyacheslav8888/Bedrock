import { createRouter, createWebHistory } from 'vue-router'
import Login from './views/Login.vue'
import Notes from './views/Notes.vue'
import TestAPI from './views/TestAPI.vue'
import authService from './services/auth'

const routes = [
  {
    path: '/',
    name: 'Login',
    component: Login
  },
  {
    path: '/notes',
    name: 'Notes',
    component: Notes,
    meta: { requiresAuth: true }
  },
  {
    path: '/test',
    name: 'TestAPI',
    component: TestAPI
  }
]

const router = createRouter({
  history: createWebHistory(),
  routes
})

// Защита маршрутов
router.beforeEach((to, from, next) => {
  if (to.meta.requiresAuth && !authService.isAuthenticated()) {
    next('/')
  } else {
    next()
  }
})

export default router