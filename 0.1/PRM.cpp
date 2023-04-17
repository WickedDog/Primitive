#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>

#define prFunction(name) void name(std::string v1 = "", std::string v2= "", std::string v3= "")

#define prCppFunction(name) void name(std::string arg) 

#define convert(v1, v2, v3) v3(v2(v1.c_str()))


class PrimitiveFunctions {
private:
	typedef void (PrimitiveFunctions::* prFunc)(std::string, std::string, std::string);

	typedef void (*prCpp)(std::string);

	struct prFuncArg {
		prFunc m_func;
		std::string v1;
		std::string v2;
		std::string v3;
	};

	std::map<std::string, std::vector<prFuncArg>> m_functions;

	//std::map<std::string, prCppFunc> m_cppfunctions;
	std::map<std::string, prCpp> m_cppfunctions;

	std::map<std::string, std::string> m_vars;
	std::string m_curWeek;

	bool lastOperation;
	bool lastStop;

	std::string m_curMark;
	std::string m_curpath;

	std::string getLastPath(std::string path) {
		std::string path_last;
		std::string all_path;
		for (size_t i = 0; i < path.size(); i++)
		{
			if (path[i] == '/' or path[i] == '\\') {
				all_path += path_last + "/";
				path_last.clear();
			}
			else {
				path_last += path[i];
			}
		}

		return all_path;
	}

	std::vector<std::string> getFromFile(std::string path) {
		std::ifstream fs(path);
		if (fs.fail()) return {};
		std::string curline;
		std::vector<std::string> tmpVec;
		while (std::getline(fs, curline))
		{
			tmpVec.push_back(curline);
		}

		fs.close();
		return tmpVec;
	}

public:
	PrimitiveFunctions() {
		m_curMark = "";
		lastOperation = false;
		lastStop = false;
	}

	void Release() {
		m_curMark = "";
		for (auto& k : m_functions)
		{
			k.second.clear();
		}

		m_cppfunctions.clear();
		m_vars.clear();
	}

	void LoadFile(std::string path) {
		auto allText = getFromFile(path);
		m_curpath = getLastPath(path);
		for (size_t i = 0; i < allText.size(); i++)
		{
			this->loadLine(allText[i]);
		}
	}

	void addVar(std::string name, std::string v) {
		m_vars[name] = v;
	}

	std::string getVar(std::string name) {
		return m_vars[name];
	}

	//**************
	//****EVENTS****
	//**************

	//***INT***
	
	//Сетать валюту/создать переменную int 
	prFunction(movint) {
		m_vars[v1] = convert(v2, std::atoi, std::to_string);
	}
	
	//Сетать существующую переменную/создать переменную int 
	prFunction(movints) {
		m_vars[v1] = convert(m_vars[v2], std::atoi, std::to_string);
	}

	//Прибавлять валюту int 
	prFunction(addint) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) + convert(v2, std::atoi));
	}

	//Прибавить на существующую валюту int 
	prFunction(addints) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) + convert(m_vars[v2], std::atoi));
	}

	//Убавлять валюту int 
	prFunction(subint) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) - convert(v2, std::atoi));
	}

	//Убавить на существующую валюту int 
	prFunction(subints) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) - convert(m_vars[v2], std::atoi));
	}

	//Умножить валюту int 
	prFunction(mulint) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) * convert(v2, std::atoi));
	}

	//Умножить на существующую валюту int 
	prFunction(mulints) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) * convert(m_vars[v2], std::atoi));
	}

	//Делить валюту int 
	prFunction(divint) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) / convert(v2, std::atoi));
	}

	//Делить на существующую валюту int 
	prFunction(divints) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) / convert(m_vars[v2], std::atoi));
	}

	//***FLOAT***

	//Сетать валюту/создать переменную float 
	prFunction(movfloat) {
		m_vars[v1] = convert(v2, std::atof, std::to_string);
	}

	//Сетать существующую переменную/создать переменную float 
	prFunction(movfloats) {
		m_vars[v1] = convert(m_vars[v2], std::atof, std::to_string);
	}

	//Прибавлять валюту float 
	prFunction(addfloat) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) + convert(v2, std::atof));
	}

	//Прибавить на существующую валюту float 
	prFunction(addfloats) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) + convert(m_vars[v2], std::atof));
	}

	//Убавлять валюту float 
	prFunction(subfloat) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) - convert(v2, std::atof));
	}

	//Убавить на существующую валюту float 
	prFunction(subfloats) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) - convert(m_vars[v2], std::atof));
	}

	//Умножить валюту float 
	prFunction(mulfloat) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) * convert(v2, std::atof));
	}

	//Умножить на существующую валюту float 
	prFunction(mulfloats) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) * convert(m_vars[v2], std::atof));
	}

	//Делить валюту float 
	prFunction(divfloat) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) / convert(v2, std::atof));
	}

	//Делить на существующую валюту float 
	prFunction(divfloats) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) / convert(m_vars[v2], std::atof));
	}

	//***STRING***

	//Сетать валюту/создать переменную string 
	prFunction(movstring) {
		m_vars[v1] = v2;
	}

	//Сетать существующую переменную/создать переменную string 
	prFunction(movstrings) {
		m_vars[v1] = m_vars[v2];
	}

	//Прибавлять валюту string 
	prFunction(addstring) {
		m_vars[v1] = m_vars[v1] + v2;
	}

	//Прибавить на существующую валюту string 
	prFunction(addstrings) {
		m_vars[v1] = m_vars[v1] + m_vars[v2];
	}

	//************
	//****MARK****
	//************

	//Начало метки
	prFunction(mark) {
		m_curMark = v1;
	}

	//Конец метки
	prFunction(end) {
		m_curMark = "";
	}

	//**************************
	//****LOGICAL OPERATIONS****
	//**************************

	//else
	prFunction(eelse) {
		if (!lastOperation) {
			for (size_t i = 0; i < m_functions[v1].size(); i++)
			{
				(this->*(m_functions[v1][i].m_func))(m_functions[v1][i].v1, m_functions[v1][i].v2, m_functions[v1][i].v3);
			}
		}
	}

	//***INT***

	//"==" int
	prFunction(ifeint) {
		if (convert(m_vars[v1], std::atoi) == convert(m_vars[v2], std::atoi))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{

				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;
		}
		else
			lastOperation = false;
	}

	//">" int
	prFunction(ifbint) {
		if (convert(m_vars[v1], std::atoi) > convert(m_vars[v2], std::atoi))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{
				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;
		}
		else
			lastOperation = false;
	}

	//">=" int
	prFunction(ifebint) {
		if (convert(m_vars[v1], std::atoi) >= convert(m_vars[v2], std::atoi))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{
				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;

		}
		else
			lastOperation = false;
	}

	//"<" int
	prFunction(iflint) {
		if (convert(m_vars[v1], std::atoi) < convert(m_vars[v2], std::atoi))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{
				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;
		}
		else
			lastOperation = false;
	}

	//"<=" int
	prFunction(ifelint) {
		if (convert(m_vars[v1], std::atoi) <= convert(m_vars[v2], std::atoi))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{
				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;
		}
		else
			lastOperation = false;
	}


	//"!=" int
	prFunction(ifneint) {
		if (convert(m_vars[v1], std::atoi) != convert(m_vars[v2], std::atoi))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{
				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;
		}
		else
			lastOperation = false;
	}

	//***FLOAT***

	//"==" float
	prFunction(ifefloat) {
		if (convert(m_vars[v1], std::atof) == convert(m_vars[v2], std::atof))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{
				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;
		}
		else
			lastOperation = false;
	}

	//">" float
	prFunction(ifbfloat) {
		if (convert(m_vars[v1], std::atof) > convert(m_vars[v2], std::atof))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{
				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;
		}
		else
			lastOperation = false;
	}

	//">=" float
	prFunction(ifebfloat) {
		if (convert(m_vars[v1], std::atof) >= convert(m_vars[v2], std::atof))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{
				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;
		}
		else
			lastOperation = false;
	}

	//"<" float
	prFunction(iflfloat) {
		if (convert(m_vars[v1], std::atof) < convert(m_vars[v2], std::atof))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{
				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;
		}
		else
			lastOperation = false;
	}

	//"<=" float
	prFunction(ifelfloat) {
		if (convert(m_vars[v1], std::atof) <= convert(m_vars[v2], std::atof))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{
				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;
		}
		else
			lastOperation = false;
	}


	//"!=" float
	prFunction(ifnefloat) {
		if (convert(m_vars[v1], std::atof) != convert(m_vars[v2], std::atof))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{
				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;
		}
		else
			lastOperation = false;
	}

	//***STRING***

	//"==" string
	prFunction(ifestring) {
		if (convert(m_vars[v1]) == convert(m_vars[v2]))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{
				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;
		}
		else
			lastOperation = false;
	}

	//"!=" string
	prFunction(ifnestring) {
		if (convert(m_vars[v1]) != convert(m_vars[v2]))
		{
			for (size_t i = 0; i < m_functions[v3].size(); i++)
			{
				(this->*(m_functions[v3][i].m_func))(m_functions[v3][i].v1, m_functions[v3][i].v2, m_functions[v3][i].v3);
			}
			lastOperation = true;
		}
		else
			lastOperation = false;
	}

	//***CALL***

	//вызов внешних функций
	prFunction(callcpp) {
		static auto findFunc = [](std::map<std::string, prCpp> prMap, std::string name) -> bool {
			for (auto &fMap : prMap)
			{
				if (fMap.first == name) {
					return true;
				}
			}

			return false;
		};
		
		if (findFunc(m_cppfunctions, v1))
			m_cppfunctions[v1]((m_vars[v2].empty() ? v2 : m_vars[v2]));
	}

	//удаление переменных
	prFunction(release) {
		m_vars[v1].clear();
	}

	//***WHILE***

	//цикл
	prFunction(repeat) {
		while (!lastStop) {
			for (size_t i = 0; i < m_functions[v1].size(); i++)
			{
				(this->*(m_functions[v1][i].m_func))(m_functions[v1][i].v1, m_functions[v1][i].v2, m_functions[v1][i].v3);
			}
		}

		lastStop = false;
	}

	//Остановка цикла
	prFunction(bbreak) {
		lastStop = true;
	}

	//***PASTE***
	prFunction(paste) {
		std::ifstream ifstr;
		ifstr.open(v1);
		if (ifstr.fail()) {
			ifstr.open(m_curpath + v1);
			if (!ifstr.fail()) {
				this->LoadFile(m_curpath + v1);
			}
		}
		else {
			this->LoadFile(v1);
		}

		ifstr.clear();

	}

	//***PARSE***
	void loadLine(std::string script) {
		static auto split = [](std::string script) -> std::vector<std::string> {
			std::vector<std::string> tmpVec;
			std::string tmpText;
			bool bText = false;

			for (size_t i = 0; i < script.size(); i++)
			{
				if ((script[i] == ' ' || script[i] == ',') && !bText) {

					if (tmpText.empty() == false) {
						tmpVec.push_back(tmpText); tmpText.clear();
					}

				}
				else if (script[i] == ';' && !bText) {
					break;
				}
				else if (script[i] == '"') {
					bText = (bText == false ? true : false);
				}
				else {
					tmpText += script[i];
				}
			}
			if (tmpText.empty() == false) {
				tmpVec.push_back(tmpText); tmpText.clear();
			}


			for (size_t i = tmpVec.size(); i <= 3; i++)
			{
				tmpVec.push_back("");
			}


			return tmpVec;
		};

		auto _split = split(script);

		//ох... это будет долго
		std::string tEvent = _split[0];
		prFuncArg setArg;
		if (tEvent == "movint") {
			setArg.m_func = &PrimitiveFunctions::movint;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "movints") {
			setArg.m_func = &PrimitiveFunctions::movints;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "addint") {
			setArg.m_func = &PrimitiveFunctions::addint;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "addints") {
			setArg.m_func = &PrimitiveFunctions::addints;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "subint") {
			setArg.m_func = &PrimitiveFunctions::subint;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "subints") {
			setArg.m_func = &PrimitiveFunctions::subints;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "mulint") {
			setArg.m_func = &PrimitiveFunctions::mulint;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "mulints") {
			setArg.m_func = &PrimitiveFunctions::mulints;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "divint") {
			setArg.m_func = &PrimitiveFunctions::divint;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "divints") {
			setArg.m_func = &PrimitiveFunctions::divints;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		//float
		else if (tEvent == "movfloat") {
			setArg.m_func = &PrimitiveFunctions::movfloat;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "movfloats") {
			setArg.m_func = &PrimitiveFunctions::movfloats;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "addfloat") {
			setArg.m_func = &PrimitiveFunctions::addfloat;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "addfloats") {
			setArg.m_func = &PrimitiveFunctions::addfloats;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "subfloat") {
			setArg.m_func = &PrimitiveFunctions::subfloat;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "subfloats") {
			setArg.m_func = &PrimitiveFunctions::subfloats;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "mulfloat") {
			setArg.m_func = &PrimitiveFunctions::mulfloat;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "mulfloats") {
			setArg.m_func = &PrimitiveFunctions::mulfloats;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "divfloat") {
			setArg.m_func = &PrimitiveFunctions::divfloat;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "divfloats") {
			setArg.m_func = &PrimitiveFunctions::divfloats;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		//string
		else if (tEvent == "movstring") {
			setArg.m_func = &PrimitiveFunctions::movstring;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "movstrings") {
			setArg.m_func = &PrimitiveFunctions::movstrings;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "addstring") {
			setArg.m_func = &PrimitiveFunctions::addstring;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "addstrings") {
			setArg.m_func = &PrimitiveFunctions::addstrings;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		//mark
		else if (tEvent == "mark") {
			mark(_split[1]);
		}
		else if (tEvent == "end") {
			mark(_split[1]);
		}
		//loperator
		else if (tEvent == "ifeint") {
			setArg.m_func = &PrimitiveFunctions::ifeint;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "ifbint") {
			setArg.m_func = &PrimitiveFunctions::ifbint;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "ifebint") {
			setArg.m_func = &PrimitiveFunctions::ifebint;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "iflint") {
			setArg.m_func = &PrimitiveFunctions::iflint;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "ifelint") {
			setArg.m_func = &PrimitiveFunctions::ifelint;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "ifneint") {
			setArg.m_func = &PrimitiveFunctions::ifneint;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		//float
		else if (tEvent == "ifefloat") {
			setArg.m_func = &PrimitiveFunctions::ifefloat;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "ifbfloat") {
			setArg.m_func = &PrimitiveFunctions::ifbfloat;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "ifebfloat") {
			setArg.m_func = &PrimitiveFunctions::ifebfloat;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "iflfloat") {
			setArg.m_func = &PrimitiveFunctions::iflfloat;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "ifelfloat") {
			setArg.m_func = &PrimitiveFunctions::ifelfloat;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "ifnefloat") {
			setArg.m_func = &PrimitiveFunctions::ifnefloat;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		//string
		else if (tEvent == "ifestring") {
			setArg.m_func = &PrimitiveFunctions::ifestring;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "ifnestring") {
			setArg.m_func = &PrimitiveFunctions::ifnestring;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "else") {
			setArg.m_func = &PrimitiveFunctions::eelse;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		//call
		else if (tEvent == "callcpp") {
			setArg.m_func = &PrimitiveFunctions::callcpp;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "release") {
			setArg.m_func = &PrimitiveFunctions::release;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}

		else if (tEvent == "repeat") {
			setArg.m_func = &PrimitiveFunctions::repeat;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}

		else if (tEvent == "break") {
			setArg.m_func = &PrimitiveFunctions::bbreak;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}
		else if (tEvent == "paste") {
			setArg.m_func = &PrimitiveFunctions::paste;
			setArg.v1 = _split[1];
			setArg.v2 = _split[2];
			setArg.v3 = _split[3];
			m_functions[m_curMark].push_back(setArg);
		}


	}

	//***START***
	void useScript() {
		for (size_t i = 0; i < m_functions[""].size(); i++)
		{
			(this->*(m_functions[""][i].m_func))(m_functions[""][i].v1, m_functions[""][i].v2, m_functions[""][i].v3);
		}
	}

	//***ADD FUNCTION***
	void loadFunction(prCpp func, std::string name){
		m_cppfunctions[name] = func;
	}

	//***DEBUG***
	void printAllVars() {
		for (auto &gh : m_vars)
		{
			std::cout << gh.first << " : " << gh.second << "\n";
		}
	}
};

PrimitiveFunctions pr;


void message(std::string text) {
	std::cout << text << "\n";
}

void tesst(std::string text) {
	std::cout << text << "\n";
}
void input_t(std::string text) {
	std::string ja;
	std::cin >> ja;
	pr.addVar("input text", ja);
}


int main() {
	//test myTest;
	//myTest.callFunction("test");

	//pr.movint("year", "2023");
	//pr.movint("age", "17");
	//pr.movints("yag", "year");
	//pr.subints("yag", "age");
	//pr.callcpp("message", "yag");

	pr.loadFunction(input_t, "input");
	pr.loadFunction(message, "message");

	pr.LoadFile("datest.prm");

	pr.useScript();

	pr.Release();
	getchar();
	//pr.printAllVars();
}
