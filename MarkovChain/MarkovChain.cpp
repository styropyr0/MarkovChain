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
			std::cout << "Processing word: " << wrapped << "\n";
			for (size_t i = 0; i < wrapped.size() - 1; ++i) {
				transitions[wrapped[i]].push_back(wrapped[i + 1]);
			}
		}
	}

	std::string generate(int maxLength = 5) {
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
};

int main() {
	srand(static_cast<unsigned>(time(0)));
	std::vector<std::string> trainingWords = {
	"flutter", "orchestra", "terminal", "alimony", "adjacent", "king", "man", "woman", "sleep", "night", "day",
	"quantum", "zephyr", "glimmer", "anchor", "breeze", "cipher", "cascade", "dawn", "ember", "fractal",
	"galaxy", "harmony", "ignite", "jovial", "kettle", "lunar", "moment", "nectar", "oracle", "prism",
	"quartz", "ripple", "sylvan", "thrust", "umbra", "vortex", "wander", "xenon", "yonder", "zenith",
	"bramble", "crimson", "drizzle", "evoke", "flicker", "glisten", "howl", "incant", "jungle", "kismet",
	"liminal", "murmur", "nimbus", "opaque", "pebble", "quiver", "rustle", "shiver", "trickle", "untold",
	"velvet", "wither", "xylem", "yearn", "zodiac", "autumn", "blossom", "cloister", "dormant", "elixir",
	"feral", "groove", "hollow", "illusion", "jester", "knight", "lantern", "mirage", "nuzzle", "obscure",
	"plume", "quaint", "relic", "serene", "tangle", "updraft", "vista", "wisp", "xanadu", "yield",
	"zealot", "arcane", "bounty", "chime", "dapple", "ethereal", "flare", "glide", "hatch", "inkling"
	};

	MarkovWordGenerator generator(trainingWords);
	std::cout << "Generated words:\n";
	for (int i = 0; i < 20; ++i) {
		std::cout << generator.generate() << "\n";
	}
	return 0;
}