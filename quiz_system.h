
// Contains all data structures, constants, and function declarations

#ifndef QUIZ_SYSTEM_H
#define QUIZ_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// ============================================================================
// CONSTANTS AND CONFIGURATION
// ============================================================================

#define MAX_QUESTIONS 1000
#define MAX_STUDENTS 100
#define MAX_STRING 512
#define MAX_CODE_LENGTH 2048
#define MAX_HINTS 3
#define MAX_KEYWORDS 10
#define NUM_C_TOPICS 12
#define MAX_DIFFICULTY 5
#define MAX_OPTIONS 4

// File paths
#define QUESTIONS_FILE "data/questions.dat"
#define STUDENTS_FILE "data/students.dat"
#define PROGRESS_FILE "data/progress.dat"
#define ANALYTICS_FILE "data/analytics.dat"

// ============================================================================
// ENUMERATIONS
// ============================================================================

typedef enum {
    MULTIPLE_CHOICE,
    CODE_OUTPUT,
    FILL_BLANK,
    DEBUG_CODE,
    TRUE_FALSE,
    CODE_COMPLETION,
    ALGORITHM_TRACE
} QuestionType;

typedef enum {
    BEGINNER = 1,
    INTERMEDIATE,
    ADVANCED,
    EXPERT
} SkillLevel;

typedef enum {
    C_BASICS = 0,
    VARIABLES_DATATYPES,
    OPERATORS_EXPRESSIONS,
    CONTROL_STRUCTURES,
    FUNCTIONS,
    ARRAYS_STRINGS,
    POINTERS,
    STRUCTURES_UNIONS,
    FILE_IO,
    MEMORY_MANAGEMENT,
    PREPROCESSOR,
    ADVANCED_C
} TopicIndex;

// ============================================================================
// DATA STRUCTURES
// ============================================================================

// Question structure
typedef struct {
    int id;
    char question[MAX_STRING];
    char options[MAX_OPTIONS][MAX_STRING];
    int correct_answer;
    char explanation[MAX_STRING];
    char code_snippet[MAX_CODE_LENGTH];
    int difficulty; // 1-5 scale
    TopicIndex topic;
    QuestionType type;
    int times_asked;
    int times_correct;
    char hints[MAX_HINTS][MAX_STRING];
    float avg_time_taken;
    char keywords[MAX_KEYWORDS][50];
    time_t date_created;
    char author[100];
} Question;

// Student performance data
typedef struct {
    char name[MAX_STRING];
    int student_id;
    float topic_scores[NUM_C_TOPICS];
    int topic_questions_attempted[NUM_C_TOPICS];
    int topic_questions_correct[NUM_C_TOPICS];
    int total_questions_attempted;
    int total_questions_correct;
    float overall_accuracy;
    int learning_streak;
    int max_streak;
    time_t last_practice;
    time_t registration_date;
    int total_study_time; // in minutes
    SkillLevel current_level;
    float predicted_exam_score;
    int interview_ready_score; // 0-100
    char weak_topics[NUM_C_TOPICS][100];
    char strong_topics[NUM_C_TOPICS][100];
    int achievements[20]; // Achievement flags
    float learning_velocity; // Questions per hour
} Student;

// AI recommendation structure
typedef struct {
    Question* recommended_question;
    float confidence_score;
    float difficulty_match;
    float topic_priority;
    char reasoning[MAX_STRING];
    char learning_objective[MAX_STRING];
} AIRecommendation;

// Session data
typedef struct {
    time_t start_time;
    time_t end_time;
    int questions_attempted;
    int questions_correct;
    float session_accuracy;
    TopicIndex primary_topic;
    SkillLevel session_level;
    int hints_used;
    float avg_response_time;
} QuizSession;

// Analytics data
typedef struct {
    int total_users;
    int total_sessions;
    float avg_accuracy;
    int most_difficult_questions[10];
    int easiest_questions[10];
    TopicIndex most_practiced_topics[NUM_C_TOPICS];
    char daily_usage[365]; // Bit array for daily usage
} SystemAnalytics;

// ============================================================================
// GLOBAL TOPIC NAMES
// ============================================================================

extern const char* c_topic_names[NUM_C_TOPICS];
extern const char* difficulty_names[MAX_DIFFICULTY];
extern const char* skill_level_names[4];

// ============================================================================
// CORE SYSTEM FUNCTIONS
// ============================================================================

// System initialization and cleanup
int initialize_quiz_system(void);
void cleanup_quiz_system(void);
int get_total_questions(void);

// Student management
void initialize_student(Student* student);
int load_student_progress(Student* student);
int save_student_progress(Student* student);
void update_student_stats(Student* student, Question* question, int is_correct, float time_taken);

// Question management
int load_questions_from_file(const char* filename);
int save_questions_to_file(const char* filename);
Question* get_question_by_id(int id);
Question* get_random_question(void);
Question* get_question_by_topic(TopicIndex topic);
int add_question(Question* new_question);

// ============================================================================
// QUIZ MODES AND FEATURES
// ============================================================================

// Main quiz functions
void run_adaptive_quiz(Student* student);
void run_topic_practice(Student* student);
void run_random_quiz(Student* student, int num_questions);
void run_timed_practice(Student* student);
void run_mock_exam(Student* student, SkillLevel level, int num_questions);
void run_interview_simulation(Student* student);

// AI-powered features
AIRecommendation get_ai_recommendation(Student* student);
void generate_ai_learning_path(Student* student);
void provide_intelligent_hint(Question* question, int wrong_answer, int hint_level);
float predict_performance(Student* student, TopicIndex topic);

// Assessment and analytics
void display_performance_dashboard(Student* student);
void generate_study_plan(Student* student);
void check_certification_eligibility(Student* student);
void export_progress_report(Student* student);

// Advanced tools
void run_code_quality_analyzer(void);
void suggest_projects(Student* student);
void run_ai_tutor_chat(Student* student);

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

// String and input utilities
char* trim_whitespace(char* str);
int get_user_choice(int min, int max);
void clear_input_buffer(void);
void wait_for_enter(void);

// Time and scoring utilities
float calculate_accuracy(int correct, int total);
float calculate_topic_mastery(Student* student, TopicIndex topic);
SkillLevel determine_skill_level(Student* student);
const char* get_topic_name(TopicIndex topic);
const char* format_time_duration(int seconds);

// File I/O utilities
int file_exists(const char* filename);
int create_directory(const char* path);
void backup_data_files(void);

// Display utilities
void display_question(Question* question);
void display_quiz_results(QuizSession* session);
void display_topic_progress(Student* student);
void display_achievements(Student* student);

// Validation functions
int validate_question(Question* question);
int validate_student_data(Student* student);

// ============================================================================
// ALGORITHM IMPLEMENTATIONS
// ============================================================================

// AI algorithms
float calculate_question_difficulty_score(Question* question, Student* student);
float calculate_topic_priority(Student* student, TopicIndex topic);
int compare_students(const void* a, const void* b);
void sort_questions_by_difficulty(Question questions[], int count);

// Statistical functions
float calculate_standard_deviation(float values[], int count);
float calculate_correlation(float x[], float y[], int count);
void perform_regression_analysis(Student* student);

// Search algorithms
Question* binary_search_question(int id);
Question** search_questions_by_keyword(const char* keyword, int* result_count);
Question** filter_questions_by_criteria(TopicIndex topic, int difficulty, int* result_count);

// ============================================================================
// INTERVIEW PREPARATION
// ============================================================================

typedef struct {
    char company_name[100];
    int difficulty_level; // 1-5
    char focus_areas[5][100];
    int typical_question_count;
    int time_limit_minutes;
} InterviewProfile;

// Interview functions
void run_company_specific_prep(Student* student, const char* company);
void generate_coding_challenges(Student* student, int difficulty);
void simulate_technical_interview(Student* student);
void provide_interview_tips(TopicIndex weak_topic);

// ============================================================================
// GAMIFICATION FEATURES
// ============================================================================

typedef enum {
    ACHIEVEMENT_FIRST_QUIZ = 0,
    ACHIEVEMENT_PERFECT_SCORE,
    ACHIEVEMENT_STREAK_5,
    ACHIEVEMENT_STREAK_10,
    ACHIEVEMENT_TOPIC_MASTER,
    ACHIEVEMENT_SPEED_DEMON,
    ACHIEVEMENT_PERSISTENT_LEARNER,
    ACHIEVEMENT_CODE_REVIEWER,
    ACHIEVEMENT_INTERVIEW_READY,
    ACHIEVEMENT_C_EXPERT
} AchievementType;

void check_achievements(Student* student, QuizSession* session);
void display_achievement_earned(AchievementType achievement);
void display_leaderboard(void);
int calculate_experience_points(Student* student);

// ============================================================================
// REPORTING AND ANALYTICS
// ============================================================================

typedef struct {
    char report_date[20];
    int total_questions_attempted;
    float overall_accuracy;
    char strongest_topic[100];
    char weakest_topic[100];
    int study_time_minutes;
    SkillLevel current_level;
    char recommendations[5][200];
} ProgressReport;

void generate_detailed_report(Student* student, ProgressReport* report);
void export_csv_report(Student* student, const char* filename);
void send_email_report(Student* student); // Placeholder for email functionality

#endif // QUIZ_SYSTEM_H
