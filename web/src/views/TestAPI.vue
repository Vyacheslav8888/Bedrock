<template>
  <div class="test-container">
    <h3>API Connection Test</h3>
    <button @click="testConnection" :disabled="testing">
      {{ testing ? "Testing..." : "Test API Connection" }}
    </button>
    <div v-if="result" class="result" :class="{ error: result.error }">
      {{ result.error || result.message }}
    </div>
  </div>
</template>

<script>
import api from "../services/api";

export default {
  name: "TestAPI",
  data() {
    return {
      testing: false,
      result: null,
    };
  },
  methods: {
    async testConnection() {
      this.testing = true;
      this.result = null;

      try {
        const response = await api.get("/");
        this.result = { message: `✅ API Connected: ${response.data.message}` };
      } catch (error) {
        this.result = { error: `❌ API Error: ${error.message}` };
      }

      this.testing = false;
    },
  },
};
</script>

<style scoped>
.test-container {
  text-align: center;
  padding: 2rem;
}

button {
  padding: 0.5rem 1rem;
  background: #667eea;
  color: white;
  border: none;
  border-radius: 5px;
  cursor: pointer;
}

button:disabled {
  background: #ccc;
  cursor: not-allowed;
}

.result {
  margin-top: 1rem;
  padding: 1rem;
  border-radius: 5px;
}

.result:not(.error) {
  background: #efe;
  color: #363;
}

.result.error {
  background: #fee;
  color: #c33;
}
</style>
