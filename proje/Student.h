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
#pragma once
#include <string>
#include <iostream>
#include <map>

class Student {
public:
	using weight_t = long double;
	using grade_t = long double;
	using letter_grade_t = std::string;
protected:
	using cache_version_t = size_t;

	static std::map<const std::string, weight_t> _weight_map;

	std::map<const std::string, grade_t> _grade_map = {
		{"Assignment_1", 0},
		{"Assignment_2", 0},
		{"Quiz_1", 0},
		{"Quiz_2", 0},
		{"Visa_1", 0},

		{"Final_1", 0},
	};

	//Cached values to avoid redundant calculations.
	grade_t _inYearAverageCache = 0;
	grade_t _endYearAverageCache = 0;
	grade_t _finalAverageCache = 0;
	letter_grade_t _finalLetterAverageCache = "FF";

	static cache_version_t _globalCacheVersion;
	cache_version_t _localCacheVersion = 0;
	bool _isCacheValid = 0;
	void _formCache();
public:
	static const weight_t MIN_WEIGHT;
	static const weight_t MAX_WEIGHT;
	static const grade_t MIN_GRADE;
	static const grade_t MAX_GRADE;

	//Checks if weight is within bounds of MIN_WEIGHT and MAX_WEIGHT.
	static bool IsValidWeight(const weight_t value);
	//Checks if grade is within bounds of MIN_GRADE and MAX_GRADE.
	static bool IsValidGrade(const grade_t value);

	static weight_t GetWeight(const std::string& name);
	static void SetWeight(const std::string& name, const weight_t value);

	const std::string FirstName;
	const std::string LastName;
	const std::string FullName;

	grade_t GetGrade(const std::string& name) const;
	void SetGrade(const std::string& name, const grade_t value);

	grade_t GetInYearAverage();
	grade_t GetEndYearAverage();
	grade_t GetFinalAverage();
	letter_grade_t GetFinalLetterAverage();

	Student(const std::string& firstName, const std::string& lastName) : FirstName{firstName}, LastName{lastName}, FullName{firstName + " " + lastName} {}

	friend std::ostream& operator<<(std::ostream& os, Student& student);
};
