const express = require('express');
const sqlite3 = require('sqlite3').verbose();
const bcrypt = require('bcrypt');
const jwt = require('jsonwebtoken');
const cors = require('cors');

const app = express();
const PORT = process.env.PORT || 3000;
const JWT_SECRET = 'your-secret-key';

app.use(express.json());
app.use(cors());

// Basic info endpoint
app.get('/api', (req, res) => {
    res.json({ 
        message: 'Bedrock Server API',
        version: '1.0.0',
        status: 'running'
    });
});

// Подключение к базе данных
const db = new sqlite3.Database('./bedrock.db', (err) => {
    if (err) {
        console.error('Database connection error:', err);
    } else {
        console.log('Connected to SQLite database');
        initializeDatabase();
    }
});

// Инициализация базы данных
function initializeDatabase() {
    const createUsersTable = `
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        )`;

    const createNotesTable = `
        CREATE TABLE IF NOT EXISTS notes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            title TEXT NOT NULL,
            content TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            updated_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (user_id) REFERENCES users (id)
        )`;

    db.run(createUsersTable);
    db.run(createNotesTable);
}

// Middleware для проверки JWT токена
function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization'];
    const token = authHeader && authHeader.split(' ')[1];

    if (!token) {
        return res.status(401).json({ error: 'Access token required' });
    }

    jwt.verify(token, JWT_SECRET, (err, user) => {
        if (err) {
            return res.status(403).json({ error: 'Invalid token' });
        }
        req.user = user;
        next();
    });
}

// API Routes

// Регистрация пользователя
app.post('/api/auth/register', async (req, res) => {
    const { username, password } = req.body;

    if (!username || !password) {
        return res.status(400).json({ error: 'Username and password required' });
    }

    try {
        const hashedPassword = await bcrypt.hash(password, 10);
        
        db.run(
            'INSERT INTO users (username, password_hash) VALUES (?, ?)',
            [username, hashedPassword],
            function(err) {
                if (err) {
                    return res.status(400).json({ error: 'User already exists' });
                }
                res.json({ message: 'User registered successfully', userId: this.lastID });
            }
        );
    } catch (error) {
        res.status(500).json({ error: 'Server error' });
    }
});

// Вход пользователя
app.post('/api/auth/login', (req, res) => {
    const { username, password } = req.body;

    db.get(
        'SELECT * FROM users WHERE username = ?',
        [username],
        async (err, user) => {
            if (err || !user) {
                return res.status(400).json({ error: 'Invalid credentials' });
            }

            try {
                if (await bcrypt.compare(password, user.password_hash)) {
                    const token = jwt.sign(
                        { id: user.id, username: user.username },
                        JWT_SECRET,
                        { expiresIn: '24h' }
                    );
                    res.json({ token, userId: user.id });
                } else {
                    res.status(400).json({ error: 'Invalid credentials' });
                }
            } catch (error) {
                res.status(500).json({ error: 'Server error' });
            }
        }
    );
});

// Получить все заметки пользователя
app.get('/api/notes', authenticateToken, (req, res) => {
    db.all(
        'SELECT * FROM notes WHERE user_id = ? ORDER BY updated_at DESC',
        [req.user.id],
        (err, notes) => {
            if (err) {
                return res.status(500).json({ error: 'Database error' });
            }
            res.json(notes || []);
        }
    );
});

// Создать новую заметку
app.post('/api/notes', authenticateToken, (req, res) => {
    const { title, content } = req.body;
    
    if (!title) {
        return res.status(400).json({ error: 'Title is required' });
    }
    
    db.run(
        'INSERT INTO notes (user_id, title, content) VALUES (?, ?, ?)',
        [req.user.id, title, content || ''],
        function(err) {
            if (err) {
                return res.status(500).json({ error: 'Database error' });
            }
            res.json({ 
                id: this.lastID, 
                title, 
                content: content || '',
                message: 'Note created successfully' 
            });
        }
    );
});

// Запуск сервера
app.listen(PORT, () => {
    console.log(`Bedrock server running on port ${PORT}`);
    console.log(`API available at http://localhost:${PORT}/api`);
});