#define _USE_MATH_DEFINES

#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>

using namespace tinyxml2;
using namespace std;
/*
	Estrutura:
	Leitura de todos os pontos dos ficheiros .3d que constam do
	ficheiro de configuracao, agrupados por instancias da classe 
	Point, que por sua vez sao convertidas e armazenadas em 
	models. Para desenhar os triangulos de uma figura, so e preciso
	ler os valores para o glVertex3f do vector dentro de cada Model.
*/
class Point{
	float x;
	float y;
	float z;
public:
	Point::Point(){}
	Point::Point(float xs, float ys, float zs){
		x=xs; y=ys; z=zs;
	}
	float getx(){return x;}
	float gety(){return y;}
	float getz(){return z;}
};
class Model{
public:
	std::vector<Point> points;
	void drawModel(){
		glBegin(GL_TRIANGLES);
		for(std::size_t i=0;i<points.size();i++){
			glColor3f(1.0,0.0,0.0);
			glVertex3f(points[i].getx(),points[i].gety(),points[i].getz());
		}
		glEnd();
	}
};
std::vector<Model> models;
void xmlParser(const char* xmlPath){
	XMLDocument file;
	XMLError nfile=file.LoadFile(xmlPath);
	if(nfile!=XML_SUCCESS){
		printf("XML File not found.\n");
		return;
	}
	XMLHandle docHandle(file.FirstChild());
	XMLElement* root=docHandle.ToElement();
	if(root==nullptr){
		printf("XML File is null.");
		return;
	}
	std::string line;
	for(XMLElement *child=root->FirstChildElement("model");child!=NULL;child=child->NextSiblingElement()){
		const char * attrib=child->Attribute("file");
		std::ifstream xmlDoc(attrib);
		if(xmlDoc.is_open()){
			/*Leitura dos pontos do ficheiro linha a linha, para o vector<Point>*/
			Model model;
			while(getline(xmlDoc,line)){
				std::stringstream stream(line);
				float px, py, pz;
				stream >> px >> py >> pz;
				Point newPoint(px,py,pz);
				model.points.push_back(newPoint);
			}
			xmlDoc.close();
			models.push_back(model);
		}
		else
			printf("Error opening XML file."+*xmlPath);
	}
}
void processModels(){
	for(std::size_t i=0;i<models.size();i++)
		models[i].drawModel();
}