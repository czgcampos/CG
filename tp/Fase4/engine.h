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
class Light{
public:
	float position[4],amb[4],diff[4],spec[4];
	Light::Light(){
		position[0]=0.0f;
		position[1]=0.0f;
		position[2]=0.0f;
		position[3]=0.0f;
		amb[0]=0.0f;
		amb[1]=0.0f;
		amb[2]=0.0f;
		amb[3]=1.0f;
		diff[0]=1.0f;
		diff[1]=1.0f;
		diff[2]=1.0f;
		diff[3]=1.0f;
		spec[0]=1.0f;
		spec[1]=1.0f;
		spec[2]=1.0f;
		spec[3]=1.0f;
	}
};
class Material{
public:
	float amb[4],diff[4],spec[4],emi[4];
	Material::Material(){
		amb[0]=0.0f;
		amb[1]=0.0f;
		amb[2]=0.0f;
		amb[3]=1.0f;
		diff[0]=1.0f;
		diff[1]=1.0f;
		diff[2]=1.0f;
		diff[3]=1.0f;
		spec[0]=1.0f;
		spec[1]=1.0f;
		spec[2]=1.0f;
		spec[3]=1.0f;
		emi[0]=0.0f;
		emi[1]=0.0f;
		emi[2]=0.0f;
		emi[3]=1.0f;
	}
};
class Model{
public:
	GLuint buffers[3];
	int nPoints;
	Material mat;
	unsigned int t,width,height,texID;
	unsigned char *texData;
	bool mater=false,textur=false;
	void drawModel(){
		if(mater){
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat.amb);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat.emi);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat.diff);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat.spec);
		}
		if(textur){
			glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
			glVertexPointer(3,GL_FLOAT,0,0);
			glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
			glNormalPointer(GL_FLOAT,0,0);
			glBindBuffer(GL_ARRAY_BUFFER,buffers[2]);
			glTexCoordPointer(2,GL_FLOAT,0,0);
			glBindTexture(GL_TEXTURE_2D,texID);
			glDrawArrays(GL_TRIANGLES,0,nPoints);
			glBindTexture(GL_TEXTURE_2D,0);
		}else{
			glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
			glVertexPointer(3,GL_FLOAT,0,0);
			glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
			glNormalPointer(GL_FLOAT,0,0);
			glBindBuffer(GL_ARRAY_BUFFER,buffers[2]);
			glDrawArrays(GL_TRIANGLES,0,nPoints);
		}
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
vector<Light> lightsGeneral;
vector<Group> groupsGeneral;
void parseLight(XMLElement* rt){
	for(XMLElement* lightsChild=rt->FirstChildElement("light");lightsChild!=nullptr;lightsChild=lightsChild->NextSiblingElement()){
		Light nl=Light();
		const char *templ=lightsChild->Attribute("type");
		if(!strcmp(templ,"POINT"))
			nl.position[3]=1.0;
		else if(!strcmp(templ,"DIRECTIONAL"))
			nl.position[3]=0.0;

		const char* lx=lightsChild->Attribute("posX");
		if(lx)
			nl.position[0]=atof(lx);
		const char* ly=lightsChild->Attribute("posY");
		if(ly)
			nl.position[1]=atof(ly);
		const char* lz=lightsChild->Attribute("posZ");
		if(lz)
			nl.position[2]=atof(lz);
		for(XMLElement* propChild=lightsChild->FirstChildElement("prop");propChild!=nullptr;propChild=propChild->NextSiblingElement()){
			const char* atR=propChild->Attribute("ambR");
			if(atR)
				nl.amb[0]=atof(atR);
			const char* atG=propChild->Attribute("ambG");
			if(atG)
				nl.amb[1]=atof(atG);
			const char* atB=propChild->Attribute("ambB");
			if(atB)
				nl.amb[2]=atof(atB);
			atR=propChild->Attribute("diffR");
			if(atR)
				nl.diff[0]=atof(atR);
			atG=propChild->Attribute("diffG");
			if(atG)
				nl.diff[1]=atof(atG);
			atB=propChild->Attribute("diffB");
			if(atB)
				nl.diff[2]=atof(atB);
			atR=propChild->Attribute("specR");
			if(atR)
				nl.spec[0]=atof(atR);
			atG=propChild->Attribute("specG");
			if(atG)
				nl.spec[1]=atof(atG);
			atB=propChild->Attribute("specB");
			if(atB)
				nl.spec[2]=atof(atB);
		}
		lightsGeneral.push_back(nl);
	}
}
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
		int np=0,vbi=0,nrmi=0,txti=0;
		float* vb=NULL;
		float* nrm=NULL;
		float* text=NULL;
		float px,py,pz,nrmx,nrmy,nrmz,txtx,txty;
		for(XMLElement* tmpModel=tmpModels->FirstChildElement("model");tmpModel!=nullptr;tmpModel=tmpModel->NextSiblingElement()){
			Model model;
			const char* textu=tmpModel->Attribute("texture");
			if(textu){
				ilInit();
				ilEnable(IL_ORIGIN_SET);
				ilGenImages(1,&model.t);
				ilBindImage(model.t);
				ILboolean success;
				success=ilLoadImage((ILstring)textu);
				if(success){
					model.width=ilGetInteger(IL_IMAGE_WIDTH);
					model.height=ilGetInteger(IL_IMAGE_HEIGHT);
					ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE);
					model.texData=ilGetData();
					glGenTextures(1,&model.texID);
					glBindTexture(GL_TEXTURE_2D,model.texID);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,model.width,model.height,0,GL_RGBA,GL_UNSIGNED_BYTE,model.texData);
					glBindTexture(GL_TEXTURE_2D,0);
				}
				else
					ILenum error=ilGetError();
				model.textur=true;
			}
			Material mt;
			const char *ambR=tmpModel->Attribute("ambR");
			if(ambR)
				mt.amb[0]=atof(ambR);
			const char *ambG=tmpModel->Attribute("ambG");
			if(ambG)
				mt.amb[1]=atof(ambG);
			const char *ambB=tmpModel->Attribute("ambB");
			if(ambB)
				mt.amb[2]=atof(ambB);
			const char *diffR=tmpModel->Attribute("diffR");
			if(diffR)
				mt.diff[0]=atof(diffR);
			const char *diffG=tmpModel->Attribute("diffG");
			if(diffG)
				mt.diff[1]=atof(diffG);
			const char *diffB=tmpModel->Attribute("diffB");
			if(diffB)
				mt.diff[2]=atof(diffB);
			const char *specR=tmpModel->Attribute("specR");
			if(specR)
				mt.spec[0]=atof(specR);
			const char *specG=tmpModel->Attribute("specG");
			if(specG)
				mt.spec[1]=atof(specG);
			const char *specB=tmpModel->Attribute("specB");
			if(specB)
				mt.spec[2]=atof(specB);
			const char *emiR=tmpModel->Attribute("emiR");
			if(emiR)
				mt.emi[0]=atof(emiR);
			const char *emiG=tmpModel->Attribute("emiG");
			if(emiG)
				mt.emi[1]=atof(emiG);
			const char *emiB=tmpModel->Attribute("emiB");
			if(emiB)
				mt.emi[2]=atof(emiB);
			if(ambR||ambG||ambB||diffR||diffG||diffB||specR||specG||specB||emiR||emiG||emiB){
				model.mat=mt;
				model.mater=true;
			}
			const char* attrib=tmpModel->Attribute("File");
			ifstream xmlDoc(attrib);
			string line;
			if(xmlDoc.is_open()){
				if(getline(xmlDoc,line)){
					stringstream streamT(line);
					streamT >> np;
					model.nPoints=np;
					vb=new float[np*3];
					nrm=new float[np*3];
					text=new float[np*2];
					while(getline(xmlDoc,line)){
						stringstream stream(line);
						stream >> px >> py >> pz >> nrmx >> nrmy >> nrmz >> txtx >> txty;
						vb[vbi++]=px;vb[vbi++]=py;vb[vbi++]=pz;nrm[nrmi++]=nrmx;nrm[nrmi++]=nrmy;nrm[nrmi++]=nrmz;text[txti++]=txtx;text[txti++]=txty;
					}
					glEnableClientState(GL_VERTEX_ARRAY);
					glEnableClientState(GL_NORMAL_ARRAY);
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					glGenBuffers(3,model.buffers);
					glBindBuffer(GL_ARRAY_BUFFER,model.buffers[0]);
					glBufferData(GL_ARRAY_BUFFER,model.nPoints*3*sizeof(float),vb,GL_STATIC_DRAW);
					glBindBuffer(GL_ARRAY_BUFFER,model.buffers[1]);
					glBufferData(GL_ARRAY_BUFFER,model.nPoints*3*sizeof(float),nrm,GL_STATIC_DRAW);
					glBindBuffer(GL_ARRAY_BUFFER,model.buffers[2]);
					glBufferData(GL_ARRAY_BUFFER,model.nPoints*2*sizeof(float),text,GL_STATIC_DRAW);
					g_modelsTmp.push_back(model);
					free(vb);
					free(nrm);
					free(text);
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
	string type;
	XMLElement* lightsElem=root->FirstChildElement("lights");
	if(lightsElem)
		parseLight(lightsElem);
	const char* tempt;
	for(XMLElement* child=root->FirstChildElement("group");child!=nullptr;child=child->NextSiblingElement()){
		tempt=child->Attribute("Name");
		type=_strdup(tempt);
		Group group=parseGroup(child,type);
		groupsGeneral.push_back(group);
	}
}