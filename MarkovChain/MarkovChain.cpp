#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

class MarkovWordGenerator {
	std::unordered_map<char, std::vector<char>> transitions;
	char startChar = '^';
	char endChar = '$';
public:
	explicit MarkovWordGenerator(const std::vector<std::string>& words) {
		for (const auto& word : words) {
			std::string wrapped = startChar + word + endChar;
			for (size_t i = 0; i < wrapped.size() - 1; ++i) {
				if (wrapped[i] == '-' || (wrapped[i] == '\n' && checkIfCharExist(transitions[wrapped[i]], '\n'))) continue;
				transitions[wrapped[i]].push_back(wrapped[i + 1]);
			}
		}
	}

	std::string generate(int maxLength = 10) {
		std::string result;
		char current = startChar;
		while (result.length() < maxLength) {
			const auto& nextOptions = transitions[current];
			if (nextOptions.empty()) break;
			char next = nextOptions[rand() % nextOptions.size()];
			if (next == endChar) break;
			result += next;
			current = next;
		}
		return result;
	}

private:
	bool checkIfCharExist(std::vector<char>& vec, char c) {
		return std::find(vec.begin(), vec.end(), c) != vec.end();
	}
};

int main() {
	srand(static_cast<unsigned>(time(0)));
	std::vector<std::string> trainingWords = {
	"The wind it hums a gentle tune,",
	"Across the hills, beneath the moon.",
	"It stirs the leaves with secret sighs,",
	"And dances low through midnight skies.",
	"It wanders through the fields alone,",
	"It whistles through the broken stone.",
	"Among the trees, it softly speaks,",
	"In voices lost to hollow peaks.",
	"It tells of stars and distant shores,",
	"Of ships that sail and open doors.",
	"Of ancient dreams and fallen kings,",
	"Of all forgotten, whispered things.",
	"It brushes past the windowpane,",
	"A lullaby in autumn rain.",
	"It carries tales of love and loss,",
	"Of bridges burned and paths we cross.",
	"It finds the places we forget,",
	"Where hope and fear and longing met.",
	"It stirs the ashes, wakes the flame,",
	"And softly calls out every name.",
	"It lingers close on sleepless nights,",
	"It turns our thoughts to ghostly lights.",
	"And as we drift in shadowed sleep,",
	"Its stories root themselves so deep.",
	"So when you feel it stroke your face,",
	"A fleeting breeze, a warm embrace—",
	"Just close your eyes and you may hear,",
	"The voice that draws your soul so near."
	};



	MarkovWordGenerator generator(trainingWords);
	std::cout << "Generated words:\n";
	for (int i = 0; i < 100; ++i) {
		std::cout << generator.generate() << " ";
	}
	return 0;
}