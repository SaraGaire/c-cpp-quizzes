// quiz_core.c - Core implementation of C Programming Quiz System
// Contains main quiz logic, AI algorithms, and system management

#include "quiz_system.h"

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

static Question question_bank[MAX_QUESTIONS];
static Student registered_students[MAX_STUDENTS];
static SystemAnalytics system_stats;
static int total_questions = 0;
static int total_students = 0;

// Topic names array
const char* c_topic_names[NUM_C_TOPICS] = {
    "C Basics & Syntax",
    "Variables & Data Types", 
    "Operators & Expressions",
    "Control Structures",
    "Functions & Recursion",
    "Arrays & Strings",
    "Pointers & Memory",
    "Structures & Unions", 
    "File Input/Output",
    "Dynamic Memory Management",
    "Preprocessor Directives",
    "Advanced C Concepts"
};

const char* difficulty_names[MAX_DIFFICULTY] = {
    "Very Easy", "Easy", "Medium", "Hard", "Very Hard"
};

const char* skill_level_names[4] = {
    "Beginner", "Intermediate", "Advanced", "Expert"
};

// ============================================================================
// SYSTEM INITIALIZATION AND MANAGEMENT
// ============================================================================

int initialize_quiz_system(void) {
    printf("🔧 Initializing quiz system components...\n");
    
    // Create data directory if it doesn't exist
    if (!file_exists("data")) {
        create_directory("data");
    }
    
    // Initialize system statistics
    memset(&system_stats, 0, sizeof(SystemAnalytics));
    
    // Load questions from data files
    if (load_questions_from_file(QUESTIONS_FILE) == 0) {
        // If no questions file exists, create default questions
        create_default_question_bank();
    }
    
    printf("✅ Quiz system initialized with %d questions\n", total_questions);
    return 0;
}

void cleanup_quiz_system(void) {
    save_questions_to_file(QUESTIONS_FILE);
    backup_data_files();
    printf("💾 System cleanup completed\n");
}

int get_total_questions(void) {
    return total_questions;
}

// ============================================================================
// QUESTION MANAGEMENT
// ============================================================================

void create_default_question_bank(void) {
    printf("📚 Creating default C programming question bank...\n");
    
    // C BASICS QUESTIONS
    add_c_basics_questions();
    add_variables_datatypes_questions();
    add_operators_expressions_questions();
    add_control_structures_questions();
    add_functions_questions();
    add_arrays_strings_questions();
    add_pointers_questions();
    add_structures_unions_questions();
    add_file_io_questions();
    add_memory_management_questions();
    add_preprocessor_questions();
    add_advanced_c_questions();
    
    printf("✅ Created %d default questions across all topics\n", total_questions);
}

void add_c_basics_questions(void) {
    Question q;
    
    // Question 1: Basic C syntax
    q.id = total_questions++;
    strcpy(q.question, "Which of the following is the correct way to include a standard library in C?");
    strcpy(q.options[0], "#include <stdio.h>");
    strcpy(q.options[1], "include stdio.h");
    strcpy(q.options[2], "#include stdio.h");
    strcpy(q.options[3], "using stdio.h");
    q.correct_answer = 0;
    strcpy(q.explanation, "Standard libraries are included using #include <library_name.h> syntax");
    q.difficulty = 1;
    q.topic = C_BASICS;
    q.type = MULTIPLE_CHOICE;
    strcpy(q.hints[0], "Think about preprocessor directives");
    strcpy(q.hints[1], "Standard libraries use angle brackets");
    strcpy(q.hints[2], "The # symbol is important for preprocessor commands");
    question_bank[q.id] = q;
    
    // Question 2: main function
    q.id = total_questions++;
    strcpy(q.question, "What is the correct signature for the main function in C?");
    strcpy(q.options[0], "void main()");
    strcpy(q.options[1], "int main()");
    strcpy(q.options[2], "main()");
    strcpy(q.options[3], "int main(void)");
    q.correct_answer = 3;
    strcpy(q.explanation, "int main(void) is the most precise way to declare main with no parameters");
    q.difficulty = 2;
    q.topic = C_BASICS;
    q.type = MULTIPLE_CHOICE;
    strcpy(q.hints[0], "Main should return an integer");
    strcpy(q.hints[1], "Use void to explicitly indicate no parameters");
    question_bank[q.id] = q;
    
    // Question 3: Code output
    q.id = total_questions++;
    strcpy(q.question, "What is the output of the following C code?");
    strcpy(q.code_snippet, 
        "#include <stdio.h>\n"
        "int main(void) {\n"
        "    printf(\"Hello, World!\\n\");\n"
        "    return 0;\n"
        "}");
    strcpy(q.options[0], "Hello, World!");
    strcpy(q.options[1], "Hello, World!\\n");
    strcpy(q.options[2], "Hello, World! followed by a newline");
    strcpy(q.options[3], "Compilation error");
    q.correct_answer = 2;
    strcpy(q.explanation, "\\n creates a newline character, so output is Hello, World! on one line followed by a newline");
    q.difficulty = 1;
    q.topic = C_BASICS;
    q.type = CODE_OUTPUT;
    strcpy(q.hints[0], "\\n represents a newline character");
    question_bank[q.id] = q;
}

void add_pointers_questions(void) {
    Question q;
    
    // Advanced pointer question
    q.id = total_questions++;
    strcpy(q.question, "What is the output of this pointer manipulation code?");
    strcpy(q.code_snippet,
        "#include <stdio.h>\n"
        "int main(void) {\n"
        "    int x = 10;\n"
        "    int *p = &x;\n"
        "    int **pp = &p;\n"
        "    printf(\"%d\", **pp);\n"
        "    return 0;\n"
        "}");
    strcpy(q.options[0], "10");
    strcpy(q.options[1], "Address of x");
    strcpy(q.options[2], "Address of p");
    strcpy(q.options[3], "Compilation error");
    q.correct_answer = 0;
    strcpy(q.explanation, "**pp dereferences twice: first *pp gives p, then *p gives x which is 10");
    q.difficulty = 4;
    q.topic = POINTERS;
    q.type = CODE_OUTPUT;
    strcpy(q.hints[0], "pp is a pointer to a pointer");
    strcpy(q.hints[1], "Each * dereferences one level");
    strcpy(q.hints[2], "**pp = *(*(pp)) = *p = x = 10");
    question_bank[q.id] = q;
    
    // Pointer arithmetic
    q.id = total_questions++;
    strcpy(q.question, "If int *p points to arr[2] where arr = {10,20,30,40,50}, what is *(p+1)?");
    strcpy(q.options[0], "20");
    strcpy(q.options[1], "30");
    strcpy(q.options[2], "40");
    strcpy(q.options[3], "Undefined behavior");
    q.correct_answer = 2;
    strcpy(q.explanation, "p points to arr[2] (value 30), so p+1 points to arr[3] (value 40)");
    q.difficulty = 3;
    q.topic = POINTERS;
    q.type = MULTIPLE_CHOICE;
    strcpy(q.hints[0], "Pointer arithmetic moves by sizeof(int) bytes");
    strcpy(q.hints[1], "p+1 moves to the next array element");
    question_bank[q.id] = q;
}

void add_memory_management_questions(void) {
    Question q;
    
    // Memory allocation
    q.id = total_questions++;
    strcpy(q.question, "Which function should be used to allocate memory for an array of 10 integers initialized to zero?");
    strcpy(q.options[0], "malloc(10 * sizeof(int))");
    strcpy(q.options[1], "calloc(10, sizeof(int))");
    strcpy(q.options[2], "realloc(NULL, 10 * sizeof(int))");
    strcpy(q.options[3], "Both A and B are correct");
    q.correct_answer = 1;
    strcpy(q.explanation, "calloc() allocates memory and initializes it to zero, malloc() doesn't initialize");
    q.difficulty = 3;
    q.topic = MEMORY_MANAGEMENT;
    q.type = MULTIPLE_CHOICE;
    strcpy(q.hints[0], "Think about which function initializes memory to zero");
    strcpy(q.hints[1], "calloc = cleared allocation");
    question_bank[q.id] = q;
    
    // Memory leak detection
    q.id = total_questions++;
    strcpy(q.question, "Identify the problem in this code:");
    strcpy(q.code_snippet,
        "void function() {\n"
        "    int *ptr = malloc(100 * sizeof(int));\n"
        "    if (ptr == NULL) return;\n"
        "    // ... use ptr ...\n"
        "    return;\n"
        "}");
    strcpy(q.options[0], "No error checking");
    strcpy(q.options[1], "Memory leak - missing free()");
    strcpy(q.options[2], "Wrong allocation size");
    strcpy(q.options[3], "Incorrect return type");
    q.correct_answer = 1;
    strcpy(q.explanation, "Memory allocated with malloc() must be freed with free() to avoid memory leaks");
    q.difficulty = 3;
    q.topic = MEMORY_MANAGEMENT;
    q.type = DEBUG_CODE;
    strcpy(q.hints[0], "What happens to allocated memory when function returns?");
    strcpy(q.hints[1], "Every malloc() needs a corresponding free()");
    question_bank[q.id] = q;
}

// ============================================================================
// STUDENT MANAGEMENT
// ============================================================================

void initialize_student(Student* student) {
    student->student_id = rand() % 10000 + 1000;
    
    // Initialize all topic scores to 0.5 (neutral starting point)
    for (int i = 0; i < NUM_C_TOPICS; i++) {
        student->topic_scores[i] = 0.5f;
        student->topic_questions_attempted[i] = 0;
        student->topic_questions_correct[i] = 0;
    }
    
    student->total_questions_attempted = 0;
    student->total_questions_correct = 0;
    student->overall_accuracy = 0.0f;
    student->learning_streak = 0;
    student->max_streak = 0;
    student->last_practice = time(NULL);
    student->registration_date = time(NULL);
    student->total_study_time = 0;
    student->current_level = BEGINNER;
    student->predicted_exam_score = 50.0f;
    student->interview_ready_score = 0;
    student->learning_velocity = 0.0f;
    
    // Initialize achievements
    memset(student->achievements, 0, sizeof(student->achievements));
    
    printf("✅ Student profile initialized for %s (ID: %d)\n", 
           student->name, student->student_id);
}

void update_student_stats(Student* student, Question* question, int is_correct, float time_taken) {
    // Update overall stats
    student->total_questions_attempted++;
    if (is_correct) {
        student->total_questions_correct++;
        student->learning_streak++;
        if (student->learning_streak > student->max_streak) {
            student->max_streak = student->learning_streak;
        }
    } else {
        student->learning_streak = 0;
    }
    
    // Update topic-specific stats
    int topic = question->topic;
    student->topic_questions_attempted[topic]++;
    if (is_correct) {
        student->topic_questions_correct[topic]++;
    }
    
    // Calculate topic score using weighted average
    float current_score = student->topic_scores[topic];
    float new_performance = is_correct ? 1.0f : 0.0f;
    float weight = 0.8f; // Weight for existing performance
    student->topic_scores[topic] = current_score * weight + new_performance * (1.0f - weight);
    
    // Update overall accuracy
    student->overall_accuracy = (float)student->total_questions_correct / student->total_questions_attempted;
    
    // Update skill level
    student->current_level = determine_skill_level(student);
    
    // Update question statistics
    question->times_asked++;
    if (is_correct) {
        question->times_correct++;
    }
    
    // Update average time
    question->avg_time_taken = (question->avg_time_taken * (question->times_asked - 1) + time_taken) / question->times_asked;
    
    student->last_practice = time(
