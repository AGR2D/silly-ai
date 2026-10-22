#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <random>
#include <windows.h>

std::vector < std::string> tokenize(const std::string& text) { // находит пробелы и делит по ним строку (раскладывает каждое слово в отдельную "коробку")
	std::vector<std::string> words;
	std::stringstream ss(text);
	std::string word;
	while (ss >> word) {
		words.push_back(word);
	}
	return words;
}

int main() {
	SetConsoleOutputCP(1251);// использует кириллицу 
	std::string training_text = "темный лес был тихим темый лес был страшным " //Переменная, куда вкидываем текст
		"рыцарь пошел в лес рыцарь достал меч "
		"меч был острым меч сверкал в темноте "
		"тихий лес скрывал тайны страшный лес пугал путников ";
	std::cout << "---Разрезаем текст на слова---\n"; // \n = ENTER; (просто перенос) endl тож, но более затратный (выталкивает весь текст сразу)

	std::vector<std::string>words = tokenize(training_text);
	std::cout << "---мозг ии (запоминание связи слов)---\n";
	std::map<std::string, std::vector<std::string>>markov_model; // создан пустой объект (переменная  markov_model) куда будут складываться пары(связи) слов
	for (size_t i = 0; i < words.size() - 1; ++i) { //создание ключа для каждого слова из текста (кроме последнего) ключ = вектор всех слов, что встречались после этого слова в тексте
		markov_model[words[i]].push_back(words[i + 1]); // 
		// вектор - значит, что у набора есть : Индексация (у каждого слова свой порядковый номер; размер (size) (у вектора есть точное кол-во элементов)
	// .push_back -  вектор автоматом выделяет доп. память и добавляет новй элемент в конец, увеличивая свой размер на 1.
	}
	std::cout << "Мозг построен. НедоИИ запомнил связи.\n\n";
	std::cout << "---Генерация текста---\n";

	std::random_device rd;
	std::mt19937 gen(rd()); // рандомайзер (хуйня какая-то)

	std::string current_word = words[0]; // берем 1-ое слово из текста как старт для генерации
	std::cout << current_word << " ";
	int words_generate = 15; // задаем кол-во слов, которые ии должен сгенерировать
	for (int i = 0; i < words_generate; ++i) { // сам цикл дя генерации
		
		const
			std::vector<std::string>& next_words = markov_model[current_word]; // получаем все слова, что могут идти после текущего слова

		if (next_words.empty()) { // если после current_word нет известных слов = выход из цикла
			std::cout << "\n[ИИ закончил и не знает, что сказать еще]\n";
			break;
		}

		std::uniform_int_distribution<> dis(0, next_words.size() - 1); // создаем "кость" для рандом выбора индекса от 0 до размера вектора - 1
		current_word = next_words[dis(gen)]; // "бросаем кость" для рандом индекса, берем слово этого индекса
		std::cout << current_word << " "; // вывод выбранного слова
	}
	if (words.size() < 2) {
		std::cout << "Слишком короткий текст для обучения\n";
		return 0;
	}
	std::cout << std::endl;
	return 0;
}