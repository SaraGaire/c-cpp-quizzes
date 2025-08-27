// Global Variables
let currentQuizData = [];
let currentQuestionIndex = 0;
let selectedAnswer = null;
let score = 0;
let quizTimer = null;
let timeRemaining = 120; // 2 minutes per question , the timing that we will give the users for answering the question.
let userAnswers = [];
let studentProgress = {
    totalQuestions: 0,
    correctAnswers: 0,
    topicScores: {},
    learningStreak: 0
};

// Sample Question Database for the question
const questionDatabase = {
    "c_basics": [
        {
            "id": 1,
            "question": "Which of the following is the correct way to include a standard library in C?",
            "code": "",
            "options": [
                "#include <stdio.h>",
                "include stdio.h",
                "#include stdio.h",
                "using stdio.h"
            ],
            "correct": 0,
            "explanation": "Standard libraries are included using #include <library_name.h> syntax",
            "topic": "C Basics",
            "difficulty": 1,
            "hints": [
                "Think about preprocessor directives",
                "Standard libraries use angle brackets",
                "The # symbol is important for preprocessor commands"
            ]
        }
    ]
};

// Initialization of the App
document.addEventListener('DOMContentLoaded', function() {
    loadUserProgress();
    updateStats();
    showNotification('Welcome to C Programming Quiz System!', 'success');
});

// Quizzes Functions
function startAdaptiveQuiz() {
    showNotification('Starting AI Adaptive Quiz...', 'success');
    const adaptiveQuestions = generateAdaptiveQuestions();
    startQuiz(adaptiveQuestions);
}
