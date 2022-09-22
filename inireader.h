#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <utility>

namespace photon {
	/*
	 Simple INI config reader. 
	 Usage:
	   photon::inireader reader("d:/git/photon/config.ini");
	   auto value1 = reader["section1"]["key1"];
	   auto value2 = reader["section2"]["key2"];
	*/

	class ini_section {		
	public:
		ini_section(const char * name = "") {
			name_ = name;
		}

		const std::string & name() const {
			return name_;
		}

		const char * get(const char * name, const char * fallback = "") {
			for (auto & pair : items_) {
				if (pair.first == name)
					return pair.second.c_str();
			}
			return (fallback);
		}

		void add(const char * key, const char * value) {
			auto item = std::make_pair(key, value);
			items_.push_back(item);
		}

		operator bool() {
			return !items_.empty();
		}

		const char * operator[](const char * key) {
			return get(key);
		}

	private:
		using item_type = std::pair<std::string, std::string>;
		std::vector<item_type> items_;
		std::string name_;
	};

	class inireader {
	public:
		inireader(std::string filename) 
		{
			FILE * fp = fopen(filename.c_str(), "rb");
			if (!fp)
				return;

			// skip utf8 bom 0xEF, 0xBB, 0xBF
			char buf[4096] = {};
			char * p = nullptr;
			char * q = nullptr;
			bool bom = false;			

			while ((p = fgets(buf, sizeof(buf), fp)) != nullptr) {
				if (!bom) {
					if (buf[0] == 0xEF && buf[1] == 0xBB && buf[2] == 0xBF) {
						p += 3;
						bom = true;
					}
				}

				p = skip_spaces(p);

				// comment or blank line
				if (*p == 0 || *p == ';')
					continue;

				if (*p == '[') {
					// section
					if ((q = strchr(p, ']')) == nullptr)
						break;
					*q = 0;
					ini_section section(++p);
					sections_.push_back(section);
				}
				else {
					if (sections_.empty())
						break;
					// pair
					if ((q = strchr(p, '=')) == nullptr)
						break;
					*q = 0;
					p = trim(p);								
					q = skip_spaces(++q);
					q = trim(q);
					sections_.back().add(p, q);
				}
			}

			if (fp) {
				fclose(fp);
			}
		}

		ini_section & section(const char * name) {
			for (auto & s : sections_) {
				if (s.name() == name)
					return (s);
			}
			return null_;
		}

		ini_section & operator[](const char * name) {
			return section(name);
		}

	protected:
		char * skip_spaces(char * p) {
			while (*p && isspace(*p))
				++p;
			return p;
		}

		char * trim(char * p) {
			size_t i = strlen(p);
			while (i > 0 && isspace(p[--i]))
				p[i] = 0;
			return p;
		}

	private:
		std::vector<ini_section> sections_;
		ini_section null_;
	};
};