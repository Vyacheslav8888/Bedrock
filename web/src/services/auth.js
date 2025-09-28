import { authAPI } from './api'

class AuthService {
  constructor() {
    this.token = localStorage.getItem('auth_token')
    this.userId = localStorage.getItem('user_id')
  }

  async register(username, password) {
    try {
      const response = await authAPI.register({ username, password })
      return { success: true, data: response.data }
    } catch (error) {
      return { success: false, error: error.response?.data?.error || 'Registration failed' }
    }
  }

  async login(username, password) {
    try {
      const response = await authAPI.login({ username, password })
      
      if (response.data.token) {
        this.token = response.data.token
        this.userId = response.data.userId
        localStorage.setItem('auth_token', this.token)
        localStorage.setItem('user_id', this.userId)
      }
      
      return { success: true, data: response.data }
    } catch (error) {
      return { success: false, error: error.response?.data?.error || 'Login failed' }
    }
  }

  logout() {
    this.token = null
    this.userId = null
    localStorage.removeItem('auth_token')
    localStorage.removeItem('user_id')
  }

  // Добавь этот метод в класс AuthService
    checkAuth() {
    if (this.token && this.userId) {
        return true
    }
    
    // Проверяем localStorage
    const token = localStorage.getItem('auth_token')
    const userId = localStorage.getItem('user_id')
    
    if (token && userId) {
        this.token = token
        this.userId = userId
        return true
    }
    
    return false
    }

  isAuthenticated() {
    return !!this.token
  }

  getToken() {
    return this.token
  }

  getUserId() {
    return this.userId
  }
}

export default new AuthService()