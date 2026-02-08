#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

struct Mark
{
    std::string subject_;
    size_t mark_;
};

struct StudentData
{
    std::string name_;
    size_t number_;
    std::vector<Mark> marks_;
};

double AverageMark(const StudentData& student)
{
    if (student.marks_.empty())
        return 0.0;

    size_t sum_of_marks = 0;

    for (const Mark& mark : student.marks_)
        sum_of_marks += mark.mark_;

    return static_cast<double>(sum_of_marks) /
        student.marks_.size();
}

size_t SumOfMarks(const StudentData& student)
{
    size_t sum_of_marks = 0;

    for (const Mark& mark : student.marks_)
        sum_of_marks += mark.mark_;

    return sum_of_marks;
}

void ReadFile(const std::string& File1, std::map<size_t, StudentData>& students)
{
    std::ifstream file(File1);

    StudentData student;
    size_t marks_count;

    while (file >> student.number_ >> student.name_ >> marks_count)
    {
        student.marks_.clear();

        for (size_t i = 0; i < marks_count; i++)
        {
            Mark mark;
            file >> mark.subject_ >> mark.mark_;
            student.marks_.push_back(mark);
        }

        students[student.number_] = student;
    }
}

void PrintSort(
    const std::map<size_t, StudentData>& students
)
{
    for (const auto& pair : students)
    {
        const StudentData& student = pair.second;

        std::cout << student.name_ << " " << student.number_ << std::endl;
    }
}

bool StudentsList(
    const StudentData& first,
    const StudentData& second
)
{
    if (first.name_ == second.name_)
    {
        return AverageMark(first) > AverageMark(second);
    }

    return first.name_ < second.name_;
}

void PrintStudentsList(
    const std::map<size_t, StudentData>& students
)
{
    std::vector<StudentData> students_vector;

    for (const auto& pair : students)
        students_vector.push_back(pair.second);

    std::sort(students_vector.begin(),
        students_vector.end(),
        StudentsList);

    for (size_t i = 0; i < students_vector.size(); ++i)
    {
        const StudentData& student = students_vector[i];
        std::cout << i + 1 << ". " << student.name_ << " " << student.number_ << " " << std::fixed << std::setprecision(2) << AverageMark(student) << std::endl;
    }
}

bool ByAverage(
    const StudentData& first,
    const StudentData& second
)
{
    return AverageMark(first) > AverageMark(second);
}

void WithAverageRange(
    const std::map<size_t, StudentData>& students,
    double minimum,
    double maximum
)
{
    std::vector<StudentData> result;

    for (const auto& pair : students)
    {
        const StudentData& student = pair.second;
        double average = AverageMark(student);

        if (average >= minimum && average <= maximum)
            result.push_back(student);
    }

    std::sort(result.begin(), result.end(), ByAverage);

    for (const StudentData& student : result)
    {
        std::cout << student.name_ << " " << AverageMark(student) << std::endl;
    }
}

void WhoPassed(
    const std::map<size_t, StudentData>& students,
    const std::string& subject_name
)
{
    for (const auto& pair : students)
    {
        const StudentData& student = pair.second;

        for (const Mark& mark : student.marks_)
        {
            if (mark.subject_ == subject_name)
            {
                std::cout << student.name_ << std::endl;
                break;
            }
        }
    }
}

void StudentCounts(
    const std::map<size_t, StudentData>& students)
{
    std::map<std::string, size_t> subject_counts;

    for (const auto& pair : students)
    {
        for (const Mark& mark : pair.second.marks_)
            subject_counts[mark.subject_]++;
    }

    for (const auto& pair : subject_counts)
    {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
}
void SubjectAverageMark(
    const std::map<size_t, StudentData>& students)
{
    std::map<std::string, std::vector<size_t>> subject_marks;

    for (const auto& pair : students)
    {
        for (const Mark& mark : pair.second.marks_)
            subject_marks[mark.subject_].push_back(mark.mark_);
    }

    std::vector<std::pair<std::string, double>> result;

    for (const auto& pair : subject_marks)
    {
        size_t sum = 0;

        for (size_t value : pair.second)
            sum += value;

        double average = static_cast<double>(sum) / pair.second.size();

        result.push_back({ pair.first, average });
    }

    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

    for (const auto& pair : result)
        std::cout << pair.first << " " << pair.second << std::endl;
}

void WithMaxMark(
    const std::map<size_t, StudentData>& students)
{
    size_t maximum_sum = 0;

    for (const auto& pair : students)
    {
        maximum_sum = std::max(maximum_sum, SumOfMarks(pair.second));
    }

    for (const auto& pair : students)
    {
        if (SumOfMarks(pair.second) == maximum_sum)
            std::cout << pair.second.name_ << std::endl;
    }
}

void WithBadMark(
    const std::map<size_t, StudentData>& students)
{
    for (const auto& pair : students)
    {
        for (const Mark& mark : pair.second.marks_)
        {
            if (mark.mark_ <= 3)
            {
                std::cout << pair.second.name_ << std::endl;
                break;
            }
        }
    }
}

int main() {

    setlocale(LC_ALL, "ru"); 
    std::map<size_t, StudentData> students;

    ReadFile("File1.txt", students);
    std::cout << "Студенты по номеру зачетки: " << std::endl;
    PrintSort(students);
    std::cout << "Средний балл студентов: " << std::endl;
    PrintStudentsList(students);
    std::cout << "Список студентов со средним баллом от 7 до 10: " << std::endl;
    WithAverageRange(students, 7.0, 10.0);
    std::cout << "Те кто сдавали математику: " << std::endl;
    WhoPassed(students, "Math");
    std::cout << "Количество студентов сдававших предмет: " << std::endl;
    StudentCounts(students);
    std::cout << "Средние оценки по предмету: " << std::endl;
    SubjectAverageMark(students);
    std::cout << "Студенты с максимальной суммой баллов: " << std::endl;
    WithMaxMark(students);
    std::cout << "Студенты с неудовлетворительной оценкой: " << std::endl;
    WithBadMark(students);

    return 0;
}
