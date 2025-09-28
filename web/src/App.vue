<template>
  <div id="app">
    <header class="header" v-if="$route.path !== '/'">
      <div class="header-content">
        <h1>📝 Bedrock Notes</h1>
        <nav class="nav">
          <router-link to="/notes">My Notes</router-link>
          <button @click="logout" class="logout-btn">Logout</button>
        </nav>
      </div>
    </header>

    <main class="main">
      <router-view />
    </main>
  </div>
</template>

<script>
import authService from "./services/auth";

export default {
  name: "App",
  methods: {
    logout() {
      authService.logout();
      this.$router.push("/");
    },
  },
};
</script>

<style>
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

body {
  font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  min-height: 100vh;
}

#app {
  min-height: 100vh;
}

.header {
  background: rgba(255, 255, 255, 0.1);
  backdrop-filter: blur(10px);
  padding: 1rem 0;
}

.header-content {
  max-width: 1200px;
  margin: 0 auto;
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0 2rem;
}

.header h1 {
  font-size: 2rem;
  font-weight: 300;
  color: white;
}

.nav {
  display: flex;
  align-items: center;
  gap: 2rem;
}

.nav a {
  color: white;
  text-decoration: none;
  font-size: 1.1rem;
}

.logout-btn {
  background: rgba(255, 255, 255, 0.2);
  color: white;
  border: 1px solid rgba(255, 255, 255, 0.3);
  padding: 0.5rem 1rem;
  border-radius: 5px;
  cursor: pointer;
  backdrop-filter: blur(10px);
}

.main {
  min-height: calc(100vh - 80px);
}
</style>
