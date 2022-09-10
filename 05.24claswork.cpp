// 24.05.22.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class TextView {
public:
	virtual string draw() = 0;
};

class Text: public TextView {
	string value;
public:
	Text(string value) {
		this->value = value;
	}
	string draw() override {
		return value;
	}
};

class DecorColorTextView: public TextView {
	virtual string pain(string tmp) = 0;
};

class ColorText: public DecorColorTextView {
	string color;
	Text *text;
public:
	ColorText(string text, string color) {
		this->text = new Text(text);
		this->color = color;
	}

	string draw() override {
		return pain(text->draw());
	}

	string pain(string tmp) override {
		//<font color = "$color">tmp</font>
		return "<font color = \"" + color + "\">" + tmp + "</font>";
	}

};

class DecorCaseText: public TextView {
protected:
	TextView *text;
	bool upper;
public:
	DecorCaseText(TextView *text, bool upper) {
		this->text = text;
		this->upper = upper;
	}
	virtual string changeCase(string tmp, bool upper) = 0;
};

class CaseText: public DecorCaseText {
public:
	CaseText(string str, bool upper = 0) :
			DecorCaseText(new Text(str), upper) {

	}
	string changeCase(string str, bool upper = 0) override {
		if (upper)
			transform(str.begin(), str.end(), str.begin(), ::toupper);
		else
			transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str;
	}
	string draw() override {
		return changeCase(this->text->draw(), this->upper);
	}
};

int main() {

	ofstream foutHTML("index.html");
	vector<TextView*> texts;
	texts.push_back(new Text("123"));
	texts.push_back(new Text("456"));
	texts.push_back(new ColorText("red", "red"));
	texts.push_back(new Text("678"));
	texts.push_back(new ColorText("eggs", "#98ff1a"));
	texts.push_back(new Text("+-="));
	texts.push_back(new ColorText("#123456", "#123456"));
	texts.push_back(new CaseText("abc1", 1));

	for (auto x : texts) {
		foutHTML << x->draw() << "<br>";
	}
}

//Декорат для текста, такой что текст автоматически становится заглавным
//*либо заглавный, либо строчной
//**Использовав Bridge
