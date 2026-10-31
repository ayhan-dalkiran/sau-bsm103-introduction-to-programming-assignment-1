/****************************************************************************
**							SAKARYA ÜNÝVERSÝTESÝ
**				 BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**					  BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**						PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**
**				ÖDEV NUMARASI....: 1
**				ÖÐRENCÝ ADI......: Ayhan Dalkýran
**				ÖÐRENCÝ NUMARASI.: g221210020
**				DERS GRUBU.......: Ýkinci Öðretim C
****************************************************************************/
#include "Student.h"
#include "Name-List.h"

template<typename TValue>
TValue vector_random_get(const std::vector<TValue>& vector) {
	return vector.at(rand() % vector.size());
}

Student::grade_t get_random_grade() {
	int bracket = rand() % 100;
	if (bracket >= 80) 
		return rand() % 21 + 80;
	else if (bracket >= 20)
		return rand() % 30 + 50;
	else
		return rand() % 50;
}

//Reads weight safely so that value is always valid.
void read_weight(const std::string& name) {
	Student::weight_t value;

	while (true) {
		std::cin >> value;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Aðýrlýk bir sayý olmalýdýr, lütfen yeni bir deðer girin: ";
			continue;
		}

		if (!Student::IsValidWeight(value)) {
			std::cout << "Aðýrlýk deðeri sýfýrdan büyük olmalýdýr, lütfen yeni bir deðer girin: ";
			continue;
		}

		Student::SetWeight(name, value);
		break;
	}
}

int main() {
	setlocale(LC_ALL, "turkish");

	std::cout << "1. ödevin aðýrlýðý giriniz:";
	read_weight("Assignment_1");
	std::cout << "2. ödevin aðýrlýðý giriniz:";
	read_weight("Assignment_2");
	std::cout << "1. kýsa sýnavýn aðýrlýðý giriniz:";
	read_weight("Quiz_1");
	std::cout << "2. kýsa sýnavýn aðýrlýðý giriniz:";
	read_weight("Quiz_2");
	std::cout << "Vize aðýrlýðý giriniz:";
	read_weight("Visa_1");
	std::cout << "Yýl içi notu aðýrlýðýný giriniz:";
	read_weight("In_Year");
	
	std::cout << "Final notu aðýrlýðýný giriniz:";
	read_weight("Final_1");
	std::cout << "Yýl sonu notu aðýrlýðýný giriniz:";
	read_weight("End_Year");

	size_t student_count;
	std::vector<std::shared_ptr<Student>> student_list{};

	std::cout << "Öðrenci sayýsýný giriniz:";
	std::cin >> student_count;

	Student::grade_t
		class_grade_sum = Student::MIN_GRADE, //Used for class_average
		class_average,
		class_standard_deviation_sum = Student::MIN_GRADE ,//Used for class_standard_deviation
		class_standard_deviation;

	//Count of students with specific letter grade.
	std::map<const Student::letter_grade_t, size_t> letter_grade_map = {
		{"AA", 0},
		{"BA", 0},
		{"BB", 0},
		{"CB", 0},
		{"CC", 0},
		{"DC", 0},
		{"DD", 0},
		{"FD", 0},
		{"FF", 0}
	};

	for (size_t _ = 1; _ <= student_count; _++) {
		std::shared_ptr<Student> student = std::make_shared<Student>(vector_random_get(FIRST_NAME_LIST), vector_random_get(LAST_NAME_LIST));
		student_list.push_back(student);

		student->SetGrade("Assignment_1", get_random_grade());
		student->SetGrade("Assignment_2", get_random_grade());
		student->SetGrade("Quiz_1", get_random_grade());
		student->SetGrade("Quiz_1", get_random_grade());
		student->SetGrade("Visa_1", get_random_grade());
		student->SetGrade("Final_1", get_random_grade());
		std::cout << *student;

		class_grade_sum += student->GetFinalAverage();

		letter_grade_map.at(student->GetFinalLetterAverage()) += 1;
	}

	class_average = class_grade_sum / student_count;

	std::shared_ptr<Student>
		min_grade_student = student_list.at(0),
		max_grade_student = student_list.at(0);

	for (auto student : student_list) {
		if (student->GetFinalAverage() < min_grade_student->GetFinalAverage())
			min_grade_student = student;
		if (student->GetFinalAverage() > max_grade_student->GetFinalAverage())
			max_grade_student = student;

		class_standard_deviation_sum += pow(student->GetFinalAverage() - class_average, 2);
	}

	class_standard_deviation = sqrt(class_standard_deviation_sum / (student_count - 1));

	std::cout << std::string(10, '=') << std::endl;
	std::cout << "Ortalama: " << class_average << std::endl;
	std::cout << "Standart Sapma: " << class_standard_deviation << std::endl;
	std::cout << "En Yüksek Not: " << max_grade_student->FullName << " : " << max_grade_student->GetFinalAverage() << std::endl;
	std::cout << "En Düþük Not: " << min_grade_student->FullName << " : " << min_grade_student->GetFinalAverage() << std::endl;
	std::cout << "Harf Notlarý: " << std::endl;
	
	for (auto& letter_grade : letter_grade_map) {
		std::cout << "\t" << letter_grade.first << ": " << letter_grade.second << std::endl;
	}

	std::cout << std::string(10, '=') << std::endl;
}
