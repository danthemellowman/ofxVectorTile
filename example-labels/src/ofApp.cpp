#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofEnableAlphaBlending();
    
//    light.setDiffuseColor(ofFloatColor(0.9));
//    light.setPosition(ofPoint(0,0,200));
//
    
    
    ofFbo::Settings settings;
    settings.width = ofGetWidth();
    settings.height = ofGetHeight();
    settings.internalformat = GL_RGB;
    settings.numSamples = 0;
    settings.useDepth = true;
    settings.useStencil = true;
    settings.depthStencilAsTexture = true;
//#ifdef TARGET_OPENGLES
//    settings.textureTarget = GL_TEXTURE_2D;
//#else
    settings.textureTarget = ofGetUsingArbTex() ? GL_TEXTURE_RECTANGLE_ARB : GL_TEXTURE_2D;
//#endif
 
    shader.load("", "shader.frag");
    
    //  Load Label Fonts
    //
    labels.loadFont("Champagne & Limousines.ttf", 10);
    labels.setFontColor(ofFloatColor(1.0), ofFloatColor(0.0));
    
    //  Link the label manager with the builder
    //
    builder.setLabelManager(&labels);
    
    //  Request a new tile to the builder
    //
//    40.7185835,-73.9572016
//40.7014042,-73.937194,16
//    38.9045675,-77.0278381
    //51.5286416,-0.1015987
//    47.5326871,7.6097155
    tileX = builder.getTileX(7.6097155);
    tileY = builder.getTileY(47.5326871);
    
    startX = tileX;
    startY = tileY;
    
    int max = 4;
    
    for(int j = 0; j < max*2; j++){
        for(int i = 0; i < max*2; i ++){
            ofPoint offset = ofPoint(startX, startY, 16);
            builder = ofxVectorBuilder();
            builder.setOffset(offset);
            builder.setLabelManager(&labels);
            tile = builder.getFromWeb(tileX,tileY,16);
            
            //  Make a VBO from the tile (FASTER)
            //
            tileMesh.append(tile.getMesh());
            if(tileX <= startX-1){
                tileX--;
            }else{
                tileX++;
            }
            
            if(tileX >= startX+max){
                tileX = startX-1;
            }

        }
        if(tileY < startY){
            tileY--;
        }else{
            tileY++;
        }
        if(tileY >=startY+max){
            tileY = startY-1;
        }
        tileX = startX;
        
    }

       fbo.allocate(settings);
}

//--------------------------------------------------------------
void ofApp::update(){
    labels.updateCameraPosition(cam.getPosition());
    
    //  Update the scene
    //
    ofEnableAlphaBlending();
    fbo.begin();
    ofClear(0,0,0,0);
    cam.begin();
    ofEnableDepthTest();
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//    ofEnableLighting();
    light.enable();
    ofSetColor(255);
    //tile.draw();
    tileMesh.draw();
    
    light.disable();
    ofDisableLighting();
    
//    labels.draw3D();
//    labels.updateProjection();
//    glDisable(GL_CULL_FACE);
    ofDisableDepthTest();
    cam.end();
    fbo.end();
    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::grey,ofColor::black);
    
    ofBackground(ofColor::black);
    
    ofSetColor(255);
    
//    if(bShader){
//        shader.begin();
//        shader.setUniformTexture("colorTex", fbo, 0);
//        shader.setUniformTexture("depthTex", fbo.getDepthTexture(), 1);
        fbo.draw(0,0);
//        shader.end();
//    } else {
//        fbo.draw(0,0);
//    }
    
    
//    labels.draw2D();
    
//    if(bShader){
        ofSetColor(0);
//    } else {
//        ofSetColor(255);
//    }
    
    ofDrawBitmapString(" 'p' : toogle point labels debug", 10,15);
    ofDrawBitmapString(" 'l' : toogle line labels debug", 10,35);
    ofDrawBitmapString(" 's' : toogle shader", 10,55);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'f'){
        ofToggleFullscreen();
    } else if (key == 'p'){
        labels.bDebugPoints = !labels.bDebugPoints;
    } else if (key == 'l'){
        labels.bDebugLines = !labels.bDebugLines;
    }else if(key == ' '){
        
        
        tileMesh.save(ofGetTimestampString()+".ply");
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    fbo.allocate(w,h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
