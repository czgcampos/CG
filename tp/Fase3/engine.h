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

using namespace tinyxml2;
using namespace std;

class Point{
public:
	float x;
	float y;
	float z;
	Point::Point(float xs,float ys,float zs){
		x=xs;y=ys;z=zs;
	}
	Point::Point(){
		x=0.0f;y=0.0f;z=0.0f;
	}
};
class Model{
public:
	GLuint buffers[1];
	int nPoints;
	void drawModel(){
		glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
		glVertexPointer(3,GL_FLOAT,0,0);
		glDrawArrays(GL_TRIANGLES,0,nPoints);
	}
};
class Translate{
public:
	vector<Point> points;
	int numbPoints;
	float time;
	Translate::Translate(vector<Point> v,float t,int n){
		points=v;
		time=t;
		numbPoints=n;
	}
	Translate::Translate(){
		points=vector<Point>();
		time=0.0f;
		numbPoints=0;
	}
};
class Rotate{
public:
	float time,x,y,z;
	Rotate::Rotate(float tmp,float xs,float ys,float zs){
		time=tmp;x=xs;y=ys;z=zs;
	}
	Rotate::Rotate(){
		time=0.0f;x=0.0f;y=0.0f;z=0.0f;
	}
};
class Rotation{
public:
	float angle,x,y,z;
	Rotation::Rotation(float ang,float xs,float ys,float zs){
		angle=ang;x=xs;y=ys;z=zs;
	}
	Rotation::Rotation(){
		angle=0.0f;x=0.0f;y=0.0f;z=0.0f;
	}
};
class Scale{
public:
	float x,y,z;
	Scale::Scale(float xs,float ys,float zs){
		x=xs;y=ys;z=zs;
	}
	Scale::Scale(){
		x=0.0f;y=0.0f;z=0.0f;
	}
};
class Color{
public:
	float r,g,b;
	Color::Color(float rs,float gs,float bs){
		r=rs/255.0f;g=gs/255.0f;b=bs/255.0f;
	}
	Color::Color(){
		r=0.0f;g=0.0f;b=0.0f;
	}
};
class Group{
public:
	string name;
	Translate t;
	Rotate r;
	Rotation rt;
	Scale s;
	Color c;
	float numberAst;
	float radiusMax;
	float radiusMin;
	vector<Model> g_models;
	vector<Group> g_groups;
	Group::Group(string nm,Translate ts,Rotate rs,Rotation rr,Scale ss,Color cs,vector<Model> m,vector<Group> g,float nA,float rMax,float rMin){
		name=nm;t=ts;r=rs;rt=rr;s=ss;c=cs;g_models=m;g_groups=g;numberAst=nA;radiusMax=rMax;radiusMin=rMin;
	}
	Group::Group(){
		string nameg;
		Translate tg;
		Rotate rg;
		Rotation rtg;
		Scale sg;
		Color cg;
		vector<Model> mds;
		vector<Group> gps;
		float nAg;
		float rMaxg;
		float rMing;
		name=nameg;t=tg;r=rg;rt=rtg;s=sg;c=cg;g_models=mds;g_groups=gps;numberAst=nAg;radiusMax=rMaxg;radiusMin=rMing;
	}
};

vector<Group> groupsGeneral;

Group parseGroup(XMLElement* child,string type){
	XMLElement* tmpTranslate=child->FirstChildElement("translate");
	int t,numbP=0;
	vector<Point> v;
	if(tmpTranslate){
		float tx=0.0f,ty=0.0f,tz=0.0f;
		const char* tempT=tmpTranslate->Attribute("Time");
		if(tempT)
			t=atoi(tempT);
		numbP=0;
		for(XMLElement* tmpPoint=tmpTranslate->FirstChildElement("point");tmpPoint!=nullptr;tmpPoint=tmpPoint->NextSiblingElement(),numbP++){
			const char* tempx=tmpPoint->Attribute("X");
			if(tempx)
				tx=atof(tempx);
			const char* tempy=tmpPoint->Attribute("Y");
			if(tempy)
				ty=atof(tempy);
			const char* tempz=tmpPoint->Attribute("Z");
			if(tempz)
				tz=atof(tempz);
			Point newPoint(tx,ty,tz);
			v.push_back(newPoint);
		}
	}
	Translate trans(v,t,numbP);
	XMLElement* tmpScale=child->FirstChildElement("scale");
	float sx=1.0f,sy=1.0f,sz=1.0f;
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
	XMLElement* tmpRotate=child->FirstChildElement("rotate");
	float rTime=0.0f,rx=0.0f,ry=0.0f,rz=0.0f;
	if(tmpRotate){
		const char* tempTime=tmpRotate->Attribute("Time");
		if(tempTime)
			rTime=atof(tempTime);
		const char* tempx=tmpRotate->Attribute("X");
		if(tempx)
			rx=atof(tempx);
		const char* tempy=tmpRotate->Attribute("Y");
		if(tempy)
			ry=atof(tempy);
		const char* tempz=tmpRotate->Attribute("Z");
		if(tempz)
			rz=atof(tempz);
	}
	Rotate rot(rTime,rx,ry,rz);
	XMLElement* tmpRotation=child->FirstChildElement("rotation");
	float rtAngle=0.0f,rtx=0.0f,rty=0.0f,rtz=0.0f;
	if(tmpRotation){
		const char* tempAngle=tmpRotation->Attribute("Angle");
		if(tempAngle)
			rtAngle=atof(tempAngle);
		const char* tempx=tmpRotation->Attribute("X");
		if(tempx)
			rtx=atof(tempx);
		const char* tempy=tmpRotation->Attribute("Y");
		if(tempy)
			rty=atof(tempy);
		const char* tempz=tmpRotation->Attribute("Z");
		if(tempz)
			rtz=atof(tempz);
	}
	Rotation rt(rtAngle,rtx,rty,rtz);
	XMLElement* tmpColor=child->FirstChildElement("color");
	float cR=0.0f,cG=0.0f,cB=0.0f;
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
	if(tmpModels){
		int np=0,j=0;
		float* vb=NULL;
		float px,py,pz;
		for(XMLElement* tmpModel=tmpModels->FirstChildElement("model");tmpModel!=nullptr;tmpModel=tmpModel->NextSiblingElement()){
			const char* attrib=tmpModel->Attribute("File");
			ifstream xmlDoc(attrib);
			string line;
			if(xmlDoc.is_open()){
				if(getline(xmlDoc,line)){
					Model model;
					stringstream streamT(line);
					streamT >> np;
					model.nPoints=np;
					vb=new float[np*3*3];
					while(getline(xmlDoc,line)){
						stringstream stream(line);
						stream >> px >> py >> pz;
						vb[j++]=px;vb[j++]=py;vb[j++]=pz;
					}
					glEnableClientState(GL_VERTEX_ARRAY);
					glGenBuffers(1,model.buffers);
					glBindBuffer(GL_ARRAY_BUFFER,model.buffers[0]);
					glBufferData(GL_ARRAY_BUFFER,model.nPoints*3*sizeof(float),vb,GL_STATIC_DRAW);
					g_modelsTmp.push_back(model);
				}
				xmlDoc.close();
			}
			else
				printf("Error opening .3d file. %s\n",attrib);
		}
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
		tempt=tmpGroups->Attribute("Name");
		type2=_strdup(tempt);
		Group tmpG=parseGroup(tmpGroups,type2);
		g_groupsTmp.push_back(tmpG);
	}
	Group gfinal(type,trans,rot,rt,sca,col,g_modelsTmp,g_groupsTmp,numberAsteroids,radiusMax,radiusMin);
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
		tempt=child->Attribute("Name");
		type=_strdup(tempt);
		Group group=parseGroup(child,type);
		groupsGeneral.push_back(group);
	}
}