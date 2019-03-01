#ifdef __APPLE__
#include "tinyxml2.h"
#include <GLUT/glut.h>
using namespace tinyxml2;
#else
#ifndef _MOTOR_H
#define _MOTOR_H
#endif
#define _USE_MATH_DEFINES
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace tinyxml2;
using namespace std;
#endif
#include <math.h>
#include <sstream>
#include <GL/glut.h>

class Point{
	float x;
	float y;
	float z;
public:
	Point::Point(){}
	Point::Point(float xs,float ys,float zs){
		x=xs;y=ys;z=zs;
	}
	float getx(){return x;}
	float gety(){return y;}
	float getz(){return z;}
};
class Model{
public:
	vector<Point> points;
	void drawModel(){
		glBegin(GL_TRIANGLES);
		for(size_t i=0;i<points.size();i++)
			glVertex3f(points[i].getx(),points[i].gety(),points[i].getz());
		glEnd();
	}
};
class Translation{
public:
	float x,y,z;
	Translation::Translation(float xs,float ys,float zs){
		x=xs;y=ys;z=zs;
	}
	Translation::Translation(){
		x=0.0;y=0.0;z=0.0;
	}
	void setX(float xs){x=xs;}
	void setY(float ys){y=ys;}
	void setZ(float zs){z=zs;}
};
class Rotation{
public:
	float angle,x,y,z;
	Rotation::Rotation(float ang,float xs,float ys,float zs){
		angle=ang;x=xs;y=ys;z=zs;
	}
	Rotation::Rotation(){
		angle=0.0;x=0.0;y=0.0;z=0.0;
	}
	void setA(float a){angle=a;}
	void setX(float xs){x=xs;}
	void setY(float ys){y=ys;}
	void setZ(float zs){z=zs;}
};
class Scale{
public:
	float x,y,z;
	Scale::Scale(float xs,float ys,float zs){
		x=xs;y=ys;z=zs;
	}
	Scale::Scale(){
		x=0.0;y=0.0;z=0.0;
	}
	void setX(float xs){x=xs;}
	void setY(float ys){y=ys;}
	void setZ(float zs){z=zs;}
};
class Color{
public:
	float r,g,b;
	Color::Color(float rs,float gs,float bs){
		r=rs/255;g=gs/255;b=bs/255;
	}
	Color::Color(){
		r=0.0;g=0.0;b=0.0;
	}
	void setR(float rs){r=rs;}
	void setG(float gs){g=gs;}
	void setB(float bs){b=bs;}
};
class Group{
public:
	string name;
	Translation t;
	Rotation r;
	Scale s;
	Color c;
	float numberAst;
	float radiusMax;
	float radiusMin;
	vector<Model> g_models;
	vector<Group> g_groups;
	Group::Group(string nm,Translation ts,Rotation rs,Scale ss,Color cs,vector<Model> m,vector<Group> g,float nA,float rMax,float rMin){
		name=nm;t=ts;r=rs;s=ss;c=cs;g_models=m;g_groups=g;numberAst=nA;radiusMax=rMax;radiusMin=rMin;
	}
	Group::Group(){
		string nameg;
		Translation tg;
		Rotation rg;
		Scale sg;
		Color cg;
		vector<Model> mds;
		vector<Group> gps;
		float nAg;
		float rMaxg;
		float rMing;
		name=nameg;t=tg;r=rg;s=sg;c=cg;g_models=mds;g_groups=gps;numberAst=nAg;radiusMax=rMaxg;radiusMin=rMing;
	}
};
vector<Group> groupsGeneral;

Group parseGroup(XMLElement* child,string type){
	XMLElement* tmpTranslation=child->FirstChildElement("translation");
	float tx=0.0,ty=0.0,tz=0.0;
	if(tmpTranslation){
		const char* tempx=tmpTranslation->Attribute("X");
		if(tempx)
			tx=atof(tempx);
		const char* tempy=tmpTranslation->Attribute("Y");
		if(tempy)
			ty=atof(tempy);
		const char* tempz=tmpTranslation->Attribute("Z");
		if(tempz)
			tz=atof(tempz);
	}
	Translation trans(tx,ty,tz);
	XMLElement* tmpScale=child->FirstChildElement("scale");
	float sx=1.0,sy=1.0,sz=1.0;
	if(tmpScale){
		const char* tempx=tmpScale->Attribute("X");
		if(tempx)
			sx=atof(tempx);
		const char* tempy=tmpScale->Attribute("Y");
		if(tempy)
			sy=atof(tempy);
		const char* tempz=tmpScale->Attribute("Z");
		if(tempz)
			sz=atof(tempz);
	}
	Scale sca(sx,sy,sz);
	XMLElement* tmpRotation=child->FirstChildElement("rotation");
	float rang=0.0,rx=0.0,ry=0.0,rz=0.0;
	if(tmpRotation){
		const char* tempang=tmpRotation->Attribute("Angle");
		if(tempang)
			rang=atof(tempang);
		const char* tempx=tmpRotation->Attribute("X");
		if(tempx)
			rx=atof(tempx);
		const char* tempy=tmpRotation->Attribute("Y");
		if(tempy)
			ry=atof(tempy);
		const char* tempz=tmpRotation->Attribute("Z");
		if(tempz)
			rz=atof(tempz);
	}
	Rotation rot(rang,rx,ry,rz);
	XMLElement* tmpColor=child->FirstChildElement("color");
	float cR=0.0,cG=0.0,cB=0.0;
	if(tmpColor){
		const char* tempx=tmpColor->Attribute("R");
		if(tempx)
			cR=atof(tempx);
		const char* tempy=tmpColor->Attribute("G");
		if(tempy)
			cG=atof(tempy);
		const char* tempz=tmpColor->Attribute("B");
		if(tempz)
			cB=atof(tempz);
	}
	Color col(cR,cG,cB);
	vector<Model> g_modelsTmp;
	XMLElement* tmpModels=child->FirstChildElement("models");
	for(XMLElement* tmpModel=tmpModels->FirstChildElement("model");tmpModel!=nullptr;tmpModel=tmpModel->NextSiblingElement()){
		const char* attrib=tmpModel->Attribute("file");
		ifstream xmlDoc(attrib);
		string line;
		if(xmlDoc.is_open()){
			Model model;
			while(getline(xmlDoc,line)){
				stringstream stream(line);
				float px,py,pz;
				stream >> px >> py >> pz;
				Point newPoint(px,py,pz);
				model.points.push_back(newPoint);
			}
			g_modelsTmp.push_back(model);
			xmlDoc.close();
		}
		else
			printf("Error opening .3d file.\n");
	}
	XMLElement* tmpNA=child->FirstChildElement("numberAsteroids");
	float numberAsteroids=0.0f;
	if(tmpNA){
		const char* na=tmpNA->Attribute("N");
		if(na)
			numberAsteroids=atof(na);
	}
	XMLElement* rMax=child->FirstChildElement("radiusMax");
	float radiusMax=0.0f;
	if(rMax){
		const char* nr1=rMax->Attribute("N");
		if(nr1)
			radiusMax=atof(nr1);
	}
	XMLElement* rMin=child->FirstChildElement("radiusMin");
	float radiusMin=0.0f;
	if(rMin){
		const char* nr2=rMin->Attribute("N");
		if(nr2)
			radiusMin=atof(nr2);
	}
	vector<Group> g_groupsTmp;
	const char* tempt;
	string type2;
	for(XMLElement* tmpGroups=child->FirstChildElement("group");tmpGroups!=nullptr;tmpGroups=tmpGroups->NextSiblingElement()){
		tempt=child->Attribute("name");
		type2=_strdup(tempt);
		Group tmpG=parseGroup(tmpGroups,type2);
		g_groupsTmp.push_back(tmpG);
	}
	Group gfinal(type,trans,rot,sca,col,g_modelsTmp,g_groupsTmp,numberAsteroids,radiusMax,radiusMin);
	return gfinal;
}
void xmlParser(const char* xmlPath){
	XMLDocument file;
	XMLError nfile=file.LoadFile(xmlPath);
	if(nfile!=XML_SUCCESS){
		cout << "Erro: ";
		file.PrintError();
		return;
	}
	XMLHandle docHandle(file.FirstChild());
	XMLElement* root=docHandle.ToElement();
	if(root==nullptr){
		printf("XML File is null.\n");
		return;
	}	
	const char* tempt;
	string type;
	for(XMLElement* child=root->FirstChildElement("group");child!=nullptr;child=child->NextSiblingElement()){
		tempt=child->Attribute("name");
		type=_strdup(tempt);
		Group group=parseGroup(child,type);
		groupsGeneral.push_back(group);
	}
}