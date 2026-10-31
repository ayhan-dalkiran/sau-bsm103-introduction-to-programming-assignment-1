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
#include <iostream>

#include "Student.h"

std::map<const std::string, Student::weight_t> Student::_weight_map = {
	{"Assignment_1", 1},
	{"Assignment_2", 1},
	{"Quiz_1", 1},
	{"Quiz_2", 1},
	{"Visa_1", 1},
	{"In_Year", 1},

	{"Final_1", 1},
	{"End_Year", 1},
};

Student::cache_version_t Student::_globalCacheVersion = 0;

void Student::_formCache() {
	//If cache is already valid, do not do any calculations.
	if (_localCacheVersion == _globalCacheVersion && _isCacheValid)
		return;

	//In-year average calculation.
	{
		const weight_t weight_sum =
			_weight_map.at("Assignment_1") +
			_weight_map.at("Assignment_2") +
			_weight_map.at("Quiz_1") +
			_weight_map.at("Quiz_2") +
			_weight_map.at("Visa_1");

		if (weight_sum != 0) {
			const grade_t weighted_grade_sum =
				(_grade_map.at("Assignment_1") * _weight_map.at("Assignment_1")) +
				(_grade_map.at("Assignment_2") * _weight_map.at("Assignment_2")) +
				(_grade_map.at("Quiz_1") * _weight_map.at("Quiz_1")) +
				(_grade_map.at("Quiz_2") * _weight_map.at("Quiz_2")) +
				(_grade_map.at("Visa_1") * _weight_map.at("Visa_1"));

			_inYearAverageCache = weighted_grade_sum / weight_sum;
		}
		else {
			_inYearAverageCache = 0;
		}
	}

	//End-year average calculation.
	{
		const weight_t weight_sum =
			_weight_map.at("Final_1");

		if (weight_sum != 0) {
			const grade_t weighted_grade_sum =
				(_grade_map.at("Final_1") * _weight_map.at("Final_1"));

			_endYearAverageCache = weighted_grade_sum / weight_sum;
		}
		else {
			_endYearAverageCache = 0;
		}
	}

	//Final average calculation.
	{
		const weight_t weight_sum =
			_weight_map.at("In_Year") +
			_weight_map.at("End_Year");

		if (weight_sum != 0) {
			const grade_t weighted_grade_sum =
				(_inYearAverageCache * _weight_map.at("In_Year")) +
				(_endYearAverageCache * _weight_map.at("End_Year"));

			_finalAverageCache = weighted_grade_sum / weight_sum;
		}
		else {
			_finalAverageCache = 0;
		}
	}

	//Final letter average calculation.
	{
		if (_finalAverageCache >= 90)
			_finalLetterAverageCache = "AA";
		else if (_finalAverageCache >= 85)
			_finalLetterAverageCache = "BA";
		else if (_finalAverageCache >= 80)
			_finalLetterAverageCache = "BB";
		else if (_finalAverageCache >= 75)
			_finalLetterAverageCache = "CB";
		else if (_finalAverageCache >= 65)
			_finalLetterAverageCache = "CC";
		else if (_finalAverageCache >= 58)
			_finalLetterAverageCache = "DC";
		else if (_finalAverageCache >= 50)
			_finalLetterAverageCache = "DD";
		else if (_finalAverageCache >= 40)
			_finalLetterAverageCache = "FD";
		else
			_finalLetterAverageCache = "FF";
	}

	//Mark cache as valid now.
	_localCacheVersion = _globalCacheVersion;
	_isCacheValid = true;
}

const Student::weight_t Student::MIN_WEIGHT = 0;
const Student::weight_t Student::MAX_WEIGHT = std::numeric_limits<Student::weight_t>::max();
const Student::grade_t Student::MIN_GRADE = 0;
const Student::grade_t Student::MAX_GRADE = 100;

bool Student::IsValidWeight(const Student::weight_t value) {
	if (value >= MIN_WEIGHT && value <= MAX_WEIGHT)
		return true;
	else
		return false;
}
bool Student::IsValidGrade(const Student::grade_t value) {
	if (value >= MIN_GRADE && value <= MAX_GRADE)
		return true;
	else
		return false;
}

Student::weight_t Student::GetWeight(const std::string& name) {
	return _weight_map.at(name);
}
void Student::SetWeight(const std::string& name, const Student::weight_t value) {
	if (!IsValidWeight(value))
		throw "weight is not valid";
	else
		_weight_map.at(name) = value;
}

Student::grade_t Student::GetGrade(const std::string& name) const {
	return _grade_map.at(name);
}
void Student::SetGrade(const std::string& name, const Student::grade_t value) {
	if (!IsValidGrade(value))
		throw "grade is not valid";
	else
		_grade_map.at(name) = value;
}

Student::grade_t Student::GetInYearAverage() {
	_formCache();
	return _inYearAverageCache;
}
Student::grade_t Student::GetEndYearAverage() {
	_formCache();
	return _endYearAverageCache;
}
Student::grade_t Student::GetFinalAverage() {
	_formCache();
	return _finalAverageCache;
}
Student::letter_grade_t Student::GetFinalLetterAverage() {
	_formCache();
	return _finalLetterAverageCache;
}

std::ostream& operator<<(std::ostream& os, Student& student) {
	static constexpr size_t output_width = 40;
	static const std::string separator(output_width, '=');

	const std::streamsize old_precision = os.precision();
	os.precision(4);

	os << separator << std::endl;
	os << "Ýsim          : " << student.FullName << std::endl;
	os << "1. Ödev       : " << student.GetGrade("Assignment_1") << std::endl;
	os << "2. Ödev       : " << student.GetGrade("Assignment_2") << std::endl;
	os << "1. Kýsa Sýnav : " << student.GetGrade("Quiz_1") << std::endl;
	os << "2. Kýsa Sýnav : " << student.GetGrade("Quiz_2") << std::endl;
	os << "Vize          : " << student.GetGrade("Visa_1") << std::endl;
	os << "Final         : " << student.GetGrade("Final_1") << std::endl;
	os << std::endl;
  
	os << "Yýl Ýçi Notu  : " << student.GetInYearAverage() << std::endl;
	os << "Yýl Sonu Notu : " << student.GetEndYearAverage() << std::endl;
	os << "Ortalama      : " << student.GetFinalAverage() << std::endl;
	os << "Harf Notu     : " << student.GetFinalLetterAverage() << std::endl;
	os << separator << std::endl;

	os.precision(old_precision);
	return os;
}
