<template>
  <div class="notes-container">
    <div class="notes-header">
      <h2>My Notes</h2>
      <button @click="showCreateForm = true" class="create-btn">
        + New Note
      </button>
    </div>

    <!-- Форма создания заметки -->
    <div v-if="showCreateForm" class="note-form">
      <h3>Create New Note</h3>
      <form @submit.prevent="createNote">
        <input
          v-model="newNote.title"
          placeholder="Title"
          required
          class="form-input"
        />
        <textarea
          v-model="newNote.content"
          placeholder="Content"
          rows="4"
          class="form-textarea"
        ></textarea>
        <div class="form-actions">
          <button type="submit" :disabled="loading">Create</button>
          <button type="button" @click="cancelCreate">Cancel</button>
        </div>
      </form>
    </div>

    <!-- Список заметок -->
    <div v-if="loading" class="loading">Loading notes...</div>

    <div v-else-if="notes.length === 0" class="empty-state">
      <p>No notes yet. Create your first note!</p>
    </div>

    <div v-else class="notes-list">
      <div v-for="note in notes" :key="note.id" class="note-card">
        <h3 class="note-title">{{ note.title }}</h3>
        <p class="note-content">{{ note.content }}</p>
        <div class="note-meta">
          <span class="note-date">{{ formatDate(note.created_at) }}</span>
          <button @click="deleteNote(note.id)" class="delete-btn">
            Delete
          </button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import { notesAPI } from "../services/api";

export default {
  name: "Notes",
  data() {
    return {
      notes: [],
      loading: false,
      showCreateForm: false,
      newNote: {
        title: "",
        content: "",
      },
    };
  },
  async mounted() {
    await this.loadNotes();
  },
  methods: {
    async loadNotes() {
      this.loading = true;
      try {
        const response = await notesAPI.getAll();
        this.notes = response.data;
      } catch (error) {
        console.error("Error loading notes:", error);
        alert("Failed to load notes");
      } finally {
        this.loading = false;
      }
    },

    async createNote() {
      if (!this.newNote.title.trim()) return;

      try {
        const response = await notesAPI.create(this.newNote);
        this.notes.unshift(response.data);
        this.cancelCreate();
        alert("Note created successfully!");
      } catch (error) {
        console.error("Error creating note:", error);
        alert("Failed to create note");
      }
    },

    async deleteNote(noteId) {
      if (!confirm("Are you sure you want to delete this note?")) return;

      try {
        await notesAPI.delete(noteId);
        this.notes = this.notes.filter((note) => note.id !== noteId);
        alert("Note deleted successfully!");
      } catch (error) {
        console.error("Error deleting note:", error);
        alert("Failed to delete note");
      }
    },

    cancelCreate() {
      this.showCreateForm = false;
      this.newNote = { title: "", content: "" };
    },

    formatDate(dateString) {
      return new Date(dateString).toLocaleDateString();
    },
  },
};
</script>

<style scoped>
.notes-container {
  max-width: 800px;
  margin: 0 auto;
  padding: 2rem;
}

.notes-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 2rem;
}

.create-btn {
  background: #28a745;
  color: white;
  border: none;
  padding: 0.75rem 1.5rem;
  border-radius: 5px;
  cursor: pointer;
  font-size: 1rem;
}

.note-form {
  background: #f8f9fa;
  padding: 1.5rem;
  border-radius: 8px;
  margin-bottom: 2rem;
}

.form-input,
.form-textarea {
  width: 100%;
  padding: 0.75rem;
  margin-bottom: 1rem;
  border: 1px solid #ddd;
  border-radius: 4px;
  font-size: 1rem;
}

.form-textarea {
  resize: vertical;
  min-height: 100px;
}

.form-actions {
  display: flex;
  gap: 1rem;
}

.form-actions button {
  padding: 0.5rem 1rem;
  border: none;
  border-radius: 4px;
  cursor: pointer;
}

.form-actions button[type="submit"] {
  background: #007bff;
  color: white;
}

.form-actions button[type="button"] {
  background: #6c757d;
  color: white;
}

.loading,
.empty-state {
  text-align: center;
  padding: 2rem;
  color: #666;
}

.notes-list {
  display: grid;
  gap: 1rem;
}

.note-card {
  background: white;
  padding: 1.5rem;
  border-radius: 8px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  border-left: 4px solid #007bff;
}

.note-title {
  margin: 0 0 0.5rem 0;
  color: #333;
}

.note-content {
  margin: 0 0 1rem 0;
  color: #666;
  line-height: 1.5;
}

.note-meta {
  display: flex;
  justify-content: space-between;
  align-items: center;
  font-size: 0.9rem;
  color: #999;
}

.delete-btn {
  background: #dc3545;
  color: white;
  border: none;
  padding: 0.25rem 0.5rem;
  border-radius: 3px;
  cursor: pointer;
  font-size: 0.8rem;
}
</style>
