<template>
  <div class="login-container">
    <div class="login-card">
      <h2>Welcome to Bedrock Notes</h2>

      <form
        @submit.prevent="isRegister ? register() : login()"
        class="login-form"
      >
        <div class="form-group">
          <input
            v-model="username"
            placeholder="Username"
            required
            class="form-input"
          />
        </div>

        <div class="form-group">
          <input
            v-model="password"
            type="password"
            placeholder="Password"
            required
            class="form-input"
          />
        </div>

        <button type="submit" class="submit-btn" :disabled="loading">
          {{ loading ? "Please wait..." : isRegister ? "Register" : "Login" }}
        </button>
      </form>

      <p class="switch-mode">
        {{ isRegister ? "Already have an account?" : "Don't have an account?" }}
        <a href="#" @click.prevent="isRegister = !isRegister">
          {{ isRegister ? "Login" : "Register" }}
        </a>
      </p>

      <div v-if="message" class="message" :class="{ error: isError }">
        {{ message }}
      </div>
    </div>
  </div>
</template>

<script>
import authService from "../services/auth";

export default {
  name: "Login",
  data() {
    return {
      username: "",
      password: "",
      isRegister: false,
      loading: false,
      message: "",
      isError: false,
    };
  },
  methods: {
    async login() {
      this.loading = true;
      this.message = "";

      const result = await authService.login(this.username, this.password);

      if (result.success) {
        this.message = "Login successful!";
        this.isError = false;
        // Перенаправление на страницу заметок
        setTimeout(() => {
          this.$router.push("/notes");
        }, 1000);
      } else {
        this.message = result.error;
        this.isError = true;
      }

      this.loading = false;
    },

    async register() {
      this.loading = true;
      this.message = "";

      const result = await authService.register(this.username, this.password);

      if (result.success) {
        this.message = "Registration successful! Please login.";
        this.isError = false;
        this.isRegister = false;
      } else {
        this.message = result.error;
        this.isError = true;
      }

      this.loading = false;
    },
  },
};
</script>

<style scoped>
.login-container {
  display: flex;
  justify-content: center;
  align-items: center;
  min-height: 60vh;
}

.login-card {
  background: white;
  padding: 2rem;
  border-radius: 10px;
  box-shadow: 0 10px 30px rgba(0, 0, 0, 0.2);
  width: 100%;
  max-width: 400px;
}

.login-card h2 {
  text-align: center;
  margin-bottom: 2rem;
  color: #333;
  font-weight: 300;
}

.form-group {
  margin-bottom: 1rem;
}

.form-input {
  width: 100%;
  padding: 0.75rem;
  border: 1px solid #ddd;
  border-radius: 5px;
  font-size: 1rem;
}

.form-input:focus {
  outline: none;
  border-color: #667eea;
}

.submit-btn {
  width: 100%;
  padding: 0.75rem;
  background: #667eea;
  color: white;
  border: none;
  border-radius: 5px;
  font-size: 1rem;
  cursor: pointer;
  transition: background 0.3s;
}

.submit-btn:hover:not(:disabled) {
  background: #5a6fd8;
}

.submit-btn:disabled {
  background: #ccc;
  cursor: not-allowed;
}

.switch-mode {
  text-align: center;
  margin-top: 1rem;
  color: #666;
}

.switch-mode a {
  color: #667eea;
  text-decoration: none;
}

.message {
  margin-top: 1rem;
  padding: 0.5rem;
  border-radius: 5px;
  text-align: center;
}

.message.error {
  background: #fee;
  color: #c33;
}

.message:not(.error) {
  background: #efe;
  color: #363;
}
</style>
