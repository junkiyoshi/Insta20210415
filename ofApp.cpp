#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	int deg_span = 10;
	int radius_span = 3;
	int radius_max = 600;

	for (int deg = 0; deg < 360; deg += deg_span) {

		for (int radius = 60; radius < radius_max; radius += radius_span) {

			auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
			auto noise_value = ofNoise(glm::vec3(noise_location * 0.2, radius * 0.01 + ofGetFrameNum() * 0.015));
			auto z = ofMap(noise_value, 0, 1, -150, 150);

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(radius * cos((deg - deg_span * 0.5 + 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5 + 0.5) * DEG_TO_RAD), z));
			vertices.push_back(glm::vec3(radius * cos((deg + deg_span * 0.5 - 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5 - 0.5) * DEG_TO_RAD), z));
			this->face.addVertices(vertices);
			this->line.addVertices(vertices);

			if (radius > 60) {

				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 4);
				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 4); this->face.addIndex(this->face.getNumVertices() - 3);

				this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 3);
				this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 4);
			}
		}

		this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateZ(ofGetFrameNum() * 0.1);

	ofSetColor(39);
	ofFill();
	ofDrawCircle(glm::vec2(), 58);
	this->face.draw();

	ofSetColor(239);
	ofNoFill();
	ofDrawCircle(glm::vec2(), 58);
	this->line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}