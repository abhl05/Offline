#include <iostream>
#include <cstring>
using namespace std;

class Course {
    string name;
    float creditHour;
public: 
    Course() {
        name = "";
        creditHour = 0.0;
    }
    Course (string name, float creditHour) {
        this->name = name;
        this->creditHour = creditHour;
    }
    string getName() {
        return name;
    }
    float getCreditHour() {
        return creditHour;
    }
    void setName(string name) {
        this->name = name;
    }
    void setCreditHour(float creditHour) {
        this->creditHour = creditHour;
    }
    void display() {
        cout << "Course Name: " << name << ", Credit Hour: " << creditHour;
    }
};

class Student {
    string name;
    int id;
    Course* courses;
    int totalCourses;
    int maxCourses;
    float* gradePoints;
public:
    Student() {
        name = "";
        id = -1;
        courses = NULL;
        totalCourses = 0;
        maxCourses = 0;
        gradePoints = NULL;
    }
    Student(string name, int id, int maxCourses) {
        this->name = name;
        this->id = id;
        this->maxCourses = maxCourses;
        totalCourses = 0;
        gradePoints = new float[maxCourses];
        courses = new Course[maxCourses];
    }
    Student(const Student &other) {
        name = other.name;
        id = other.id;
        maxCourses = other.maxCourses;
        totalCourses = other.totalCourses;
        gradePoints = new float[maxCourses];
        courses = new Course[maxCourses];
        for(int i = 0; i < totalCourses; i++) {
            courses[i] = other.courses[i];
            gradePoints[i] = other.gradePoints[i];
        }
    }
    ~Student() {
        if(courses) delete[] courses;
        if(gradePoints) delete[] gradePoints;
    }
    void setName(string name) {
        this->name = name;
    }
    void setId(int id) {
        this->id = id;
    }
    void setInfo(string name, int id) {
        this->name = name;
        this->id = id;
    }
    void addCourse(Course  c) {
        if(totalCourses == maxCourses) {
            cout << "Cannot add more courses to " + name << endl;
            return;
        }
        courses[totalCourses] = c;
        gradePoints[totalCourses] = 0.0;
        totalCourses++;
    }
    void addCourse(Course course, float gradePoint) {
        if(totalCourses == maxCourses) {
            cout << "Cannot add more courses to " + name << endl;
            return;
        }
        courses[totalCourses] = course;
        gradePoints[totalCourses] = gradePoint;
        totalCourses++;
    }
    void setGradePoint(Course c, float gradePoint) {
        for(int i = 0; i < totalCourses; i++) {
            if(courses[i].getName() == c.getName() && courses[i].getCreditHour() == c.getCreditHour()) {
                gradePoints[i] = gradePoint;
                return;
            }
        }
    }
    void setGradePoint(float* gradePoints, int n) {
        if(n > totalCourses) return;
        for(int i = 0; i < n; i++) {
            this->gradePoints[i] = gradePoints[i];
        }
    }
    string getName() {
        return name;
    }
    float getCGPA() {
        float CGPA = 0.0;
        float totalCredit = 0.0;
        for(int i = 0; i < totalCourses; i++) {
            CGPA += courses[i].getCreditHour()*gradePoints[i];
            totalCredit+=courses[i].getCreditHour();
        }
        return CGPA/totalCredit;
    }
    float getGradePoint(Course c) {
        for(int i = 0; i < totalCourses; i++) {
            if(courses[i].getName() == c.getName() && courses[i].getCreditHour() == c.getCreditHour()) {
                return gradePoints[i];
            } 
        }
    }
    int getTotalCourses() {
        return totalCourses;
    }
    float getTotalCreditHours() {
        float totalCreditHours = 0.0;
        for(int i = 0; i < totalCourses; i++) {
            totalCreditHours += (gradePoints[i] >= 2.0 ? courses[i].getCreditHour() : 0.0);
        }
        return totalCreditHours;
    }
    Course getMostFavoriteCourse() {
        float maxGrade = -1.0;
        int maxGradeIdx = -1;
        for(int i = 0; i < totalCourses; i++) {
            if(gradePoints[i] > maxGrade) {
                maxGrade = gradePoints[i];
                maxGradeIdx = i;
            }
        }
        return courses[maxGradeIdx];
    }
    Course getLeastFavoriteCourse() {
        float minGrade = 5.0;
        int minGradeIdx = -1;
        for(int i = 0; i < totalCourses; i++) {
            if(gradePoints[i] < minGrade) {
                minGrade = gradePoints[i];
                minGradeIdx = i;
            }
        }
        return courses[minGradeIdx];
    }
    Course* getFailedCourses(int &count) {
        count = 0;
        for(int i = 0; i < totalCourses; i++) {
            if(gradePoints[i] < 2.00) {
                count++;
            }
        }
        Course* failedCourses = new Course[count];
        int idx = 0;
        for(int i = 0; i < totalCourses; i++) {
            if(gradePoints[i] < 2.00) {
                failedCourses[idx++] = courses[i];
            }
        }
        return failedCourses;
    }
    void display() {
        cout << "==================================\n";
        cout << "Student Name: " << name << ", ID: " << id << endl;
        for(int i = 0; i < totalCourses; i++) {
            courses[i].display();
            cout << ", gradePoint: " << gradePoints[i] << endl;
        }
        cout << "CGPA: " << getCGPA() << endl;
        cout << "Total Credit Hours Earned: " << getTotalCreditHours() << endl;
        cout << "Most Favorite Course: " << getMostFavoriteCourse().getName() << endl;
        cout << "Least Favorite Course: " << getLeastFavoriteCourse().getName() << endl;
        cout << "==================================\n";
    }
};

Student** students = new Student*[100000];
int totalStudents;

Student getTopper() {
    float maxCGPA = -1.0;
    int maxCGPAidx = -1;
    for(int i = 0; i < totalStudents; i++) {
        if(students[i]->getCGPA() > maxCGPA) {
            maxCGPA = students[i]->getCGPA();
            maxCGPAidx = i;
        }
    }
    return *students[maxCGPAidx];
}

Student getTopper(Course c) {
    float maxCGPA = -1.0;
    int maxCGPAidx = -1;
    for(int i = 0; i < totalStudents; i++) {
        if(students[i]->getGradePoint(c) > maxCGPA) {
            maxCGPA = students[i]->getGradePoint(c);
            maxCGPAidx = i;
        }
    }
    return *students[maxCGPAidx];
}

int main() { 
    // generate courses 
    const int COURSE_COUNT = 6; 
    Course courses[COURSE_COUNT] = { 
    Course("CSE107", 3), 
    Course("CSE105", 3), 
    Course("CSE108", 1.5), 
    Course("CSE106", 1.5), 
    Course("EEE164", 0.75), 
    Course("ME174", 0.75), 
    }; 
    float gradePoints[COURSE_COUNT] = {4.0, 4.0, 3.5, 3.5, 4.0, 3.25}; 
    // generate students 
    Student s1 = Student("Sheldon", 1, 5); 
    students[totalStudents++] = &s1; 
    // add courses to s1 
    s1.addCourse(courses[0]); 
    s1.addCourse(courses[1]); 
    s1.addCourse(courses[2]); 
    s1.addCourse(courses[3]); 
    s1.addCourse(courses[4]); 
    s1.addCourse(courses[5]); 
    s1.setGradePoint (gradePoints, s1.getTotalCourses()); 
    s1.display(); 
    Student s2 = Student("Penny", 2, 5); 
    students[totalStudents++] = &s2; 
    s2.addCourse(courses[0]); 
    s2.addCourse(courses[2]); 
    s2.addCourse(courses[5]); 
    s2.setGradePoint (gradePoints, s2.getTotalCourses()); 
    s2.setGradePoint (courses[0], 3.25); 
    s2.display(); 
    Student s3 = s2; 
    students[totalStudents++] = &s3; 
    s3.setName("Leonard"); 
    s3.setId(3); 
    s3.setGradePoint (gradePoints, s3.getTotalCourses()); 
    s3.addCourse(courses[1], 3.75); 
    s3.display(); 
    Student s4 = s3; 
    students[totalStudents++] = &s4; 
    s4.setInfo("Howard", 4); 
    s4.setGradePoint (gradePoints, s4.getTotalCourses()); 
    s4.addCourse(courses[3], 3.75); 
    s4.display(); 
    Student s5 = s4; 
    students[totalStudents++] = &s5; 
    s5.setInfo("Raj", 5); 
    s5.setGradePoint (gradePoints, s5.getTotalCourses()); 
    s5.setGradePoint (courses[0], 1.5); 
    s5.setGradePoint (courses[2], 2.0); 
    s5.setGradePoint (courses[5], 1.75); 
    s5.setGradePoint (courses[3], 3.75); 
    s5.display(); 
    int failedCount; 
    Course* failedCourses = s5.getFailedCourses(failedCount); 
    cout << "Failed Courses for " << s5.getName() << ":" << endl; 
    for (int i = 0; i < failedCount; ++i) { 
    failedCourses[i].display(); 
    cout << endl; 
    } 
    delete[] failedCourses; 
    cout << "==================================" << endl; 
    Student topper = getTopper(); 
    cout << "Topper: " << topper.getName() << endl; 
    cout << "Topper CGPA: " << topper.getCGPA() << endl; 
    cout << "==================================" << endl; 
    for (int i = 0; i < COURSE_COUNT; ++i) { 
    Course c = courses[i]; 
    Student topperInCourse = getTopper(c); 
    cout << "Topper in " << c.getName() << ": " << 
    topperInCourse.getName() << endl; 
    cout << "Topper in " << c.getName() << " gradePoint: " << 
    topperInCourse. getGradePoint (c) << endl; 
    cout << "==================================" << endl; 
    } 
    return 0; 
} 
    
/*
Expected Output: 
Cannot add more courses to Sheldon 
================================== 
Student Name: Sheldon, ID: 1 
Course Name: CSE107, Credit Hour: 3, gradePoint: 4 
Course Name: CSE105, Credit Hour: 3, gradePoint: 4 
Course Name: CSE108, Credit Hour: 1.5, gradePoint: 3.5 
Course Name: CSE106, Credit Hour: 1.5, gradePoint: 3.5 
Course Name: EEE164, Credit Hour: 0.75, gradePoint: 4 
CGPA: 3.84615 
Total Credit Hours Earned: 9.75 
Most Favorite Course: CSE107 
Least Favorite Course: CSE108 
================================== 
================================== 
Student Name: Penny, ID: 2 
Course Name: CSE107, Credit Hour: 3, gradePoint: 3.25 
Course Name: CSE108, Credit Hour: 1.5, gradePoint: 4 
Course Name: ME174, Credit Hour: 0.75, gradePoint: 3.5 
CGPA: 3.5 
Total Credit Hours Earned: 5.25 
Most Favorite Course: CSE108 
Least Favorite Course: CSE107 
================================== 
================================== 
Student Name: Leonard, ID: 3 
Course Name: CSE107, Credit Hour: 3, gradePoint: 4 
Course Name: CSE108, Credit Hour: 1.5, gradePoint: 4 
Course Name: ME174, Credit Hour: 0.75, gradePoint: 3.5 
Course Name: CSE105, Credit Hour: 3, gradePoint: 3.75 
CGPA: 3.86364 
Total Credit Hours Earned: 8.25 
Most Favorite Course: CSE107 
Least Favorite Course: ME174 
================================== 
================================== 
Student Name: Howard, ID: 4 
Course Name: CSE107, Credit Hour: 3, gradePoint: 4 
Course Name: CSE108, Credit Hour: 1.5, gradePoint: 4 
Course Name: ME174, Credit Hour: 0.75, gradePoint: 3.5 
Course Name: CSE105, Credit Hour: 3, gradePoint: 3.5 
Course Name: CSE106, Credit Hour: 1.5, gradePoint: 3.75 
CGPA: 3.76923 
Total Credit Hours Earned: 9.75 
Most Favorite Course: CSE107 
Least Favorite Course: ME174 
================================== 
================================== 
Student Name: Raj, ID: 5 
Course Name: CSE107, Credit Hour: 3, gradePoint: 1.5 
Course Name: CSE108, Credit Hour: 1.5, gradePoint: 2 
Course Name: ME174, Credit Hour: 0.75, gradePoint: 1.75 
Course Name: CSE105, Credit Hour: 3, gradePoint: 3.5 
Course Name: CSE106, Credit Hour: 1.5, gradePoint: 3.75 
CGPA: 2.55769 
Total Credit Hours Earned: 6 
Most Favorite Course: CSE106 
Least Favorite Course: CSE107 
================================== 
Failed Courses for Raj: 
Course Name: CSE107, Credit Hour: 3 
Course Name: ME174, Credit Hour: 0.75 
================================== 
Topper: Leonard 
Topper CGPA: 3.86364 
================================== 
Topper in CSE107: Sheldon 
Topper in CSE107 gradePoint: 4 
================================== 
Topper in CSE105: Sheldon 
Topper in CSE105 gradePoint: 4 
================================== 
Topper in CSE108: Penny 
Topper in CSE108 gradePoint: 4 
================================== 
Topper in CSE106: Howard 
Topper in CSE106 gradePoint: 3.75 
================================== 
Topper in EEE164: Sheldon 
Topper in EEE164 gradePoint: 4 
================================== 
Topper in ME174: Penny 
Topper in ME174 gradePoint: 3.5 
================================== 
*/