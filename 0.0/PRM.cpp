#include <iostream>
#include <map>
#include <vector>
#include <string>
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

	bool lastOperation;
	bool lastStop;

	std::string m_curMark;
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
	
	//Ñåòàòü âàëþòó/ñîçäàòü ïåðåìåííóþ int 
	prFunction(movint) {
		m_vars[v1] = convert(v2, std::atoi, std::to_string);
	}
	
	//Ñåòàòü ñóùåñòâóþùóþ ïåðåìåííóþ/ñîçäàòü ïåðåìåííóþ int 
	prFunction(movints) {
		m_vars[v1] = convert(m_vars[v2], std::atoi, std::to_string);
	}

	//Ïðèáàâëÿòü âàëþòó int 
	prFunction(addint) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) + convert(v2, std::atoi));
	}

	//Ïðèáàâèòü íà ñóùåñòâóþùóþ âàëþòó int 
	prFunction(addints) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) + convert(m_vars[v2], std::atoi));
	}

	//Óáàâëÿòü âàëþòó int 
	prFunction(subint) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) - convert(v2, std::atoi));
	}

	//Óáàâèòü íà ñóùåñòâóþùóþ âàëþòó int 
	prFunction(subints) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) - convert(m_vars[v2], std::atoi));
	}

	//Óìíîæèòü âàëþòó int 
	prFunction(mulint) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) * convert(v2, std::atoi));
	}

	//Óìíîæèòü íà ñóùåñòâóþùóþ âàëþòó int 
	prFunction(mulints) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) * convert(m_vars[v2], std::atoi));
	}

	//Äåëèòü âàëþòó int 
	prFunction(divint) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) / convert(v2, std::atoi));
	}

	//Äåëèòü íà ñóùåñòâóþùóþ âàëþòó int 
	prFunction(divints) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atoi) / convert(m_vars[v2], std::atoi));
	}

	//***FLOAT***

	//Ñåòàòü âàëþòó/ñîçäàòü ïåðåìåííóþ float 
	prFunction(movfloat) {
		m_vars[v1] = convert(v2, std::atof, std::to_string);
	}

	//Ñåòàòü ñóùåñòâóþùóþ ïåðåìåííóþ/ñîçäàòü ïåðåìåííóþ float 
	prFunction(movfloats) {
		m_vars[v1] = convert(m_vars[v2], std::atof, std::to_string);
	}

	//Ïðèáàâëÿòü âàëþòó float 
	prFunction(addfloat) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) + convert(v2, std::atof));
	}

	//Ïðèáàâèòü íà ñóùåñòâóþùóþ âàëþòó float 
	prFunction(addfloats) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) + convert(m_vars[v2], std::atof));
	}

	//Óáàâëÿòü âàëþòó float 
	prFunction(subfloat) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) - convert(v2, std::atof));
	}

	//Óáàâèòü íà ñóùåñòâóþùóþ âàëþòó float 
	prFunction(subfloats) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) - convert(m_vars[v2], std::atof));
	}

	//Óìíîæèòü âàëþòó float 
	prFunction(mulfloat) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) * convert(v2, std::atof));
	}

	//Óìíîæèòü íà ñóùåñòâóþùóþ âàëþòó float 
	prFunction(mulfloats) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) * convert(m_vars[v2], std::atof));
	}

	//Äåëèòü âàëþòó float 
	prFunction(divfloat) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) / convert(v2, std::atof));
	}

	//Äåëèòü íà ñóùåñòâóþùóþ âàëþòó float 
	prFunction(divfloats) {
		m_vars[v1] = std::to_string(convert(m_vars[v1], std::atof) / convert(m_vars[v2], std::atof));
	}

	//***STRING***

	//Ñåòàòü âàëþòó/ñîçäàòü ïåðåìåííóþ string 
	prFunction(movstring) {
		m_vars[v1] = v2;
	}

	//Ñåòàòü ñóùåñòâóþùóþ ïåðåìåííóþ/ñîçäàòü ïåðåìåííóþ string 
	prFunction(movstrings) {
		m_vars[v1] = m_vars[v2];
	}

	//Ïðèáàâëÿòü âàëþòó string 
	prFunction(addstring) {
		m_vars[v1] = m_vars[v1] + v2;
	}

	//Ïðèáàâèòü íà ñóùåñòâóþùóþ âàëþòó string 
	prFunction(addstrings) {
		m_vars[v1] = m_vars[v1] + m_vars[v2];
	}

	//************
	//****MARK****
	//************

	//Íà÷àëî ìåòêè
	prFunction(mark) {
		m_curMark = v1;
	}

	//Êîíåö ìåòêè
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

	//âûçîâ âíåøíèõ ôóíêöèé
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
		
		if(findFunc(m_cppfunctions, v1))
			m_cppfunctions[v1](m_vars[v2]);
	}

	//óäàëåíèå ïåðåìåííûõ
	prFunction(release) {
		m_vars[v1].clear();
	}

	//***WHILE***

	//öèêë
	prFunction(repeat) {
		while (!lastStop) {
			for (size_t i = 0; i < m_functions[v1].size(); i++)
			{
				(this->*(m_functions[v1][i].m_func))(m_functions[v1][i].v1, m_functions[v1][i].v2, m_functions[v1][i].v3);
			}
		}

		lastStop = false;
	}

	//Îñòàíîâêà öèêëà
	prFunction(bbreak) {
		lastStop = true;
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

		//îõ... ýòî áóäåò äîëãî
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
