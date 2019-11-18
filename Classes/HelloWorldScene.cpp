/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
       // this->addChild(sprite, 0);
    }
	//OpenGL�̃G���[�R�[�h���󂯂�
	GLenum error;

	m_pProgram = new GLProgram;

	//�V�F�[�_���e�L�X�g�t�@�C������ǂݍ���ŃR���p�C��
	m_pProgram->initWithFilenames("shaders/shader_0tex.vsh", "shaders/shader_0tex.fsh");
	error = glGetError();

	//attribute�ϐ��ɑ����C���f�B�b�N�X������U��
	m_pProgram->bindAttribLocation("a_position", GLProgram::VERTEX_ATTRIB_POSITION);
	error = glGetError();

	//attribute�ϐ��ɑ����C���f�B�b�N�X������U��
	m_pProgram->bindAttribLocation("a_color", GLProgram::VERTEX_ATTRIB_COLOR);
	error = glGetError();

	//attribute�ϐ��ɑ����C���f�B�b�N�X������U��
	m_pProgram->bindAttribLocation("a_texCoord", GLProgram::VERTEX_ATTRIB_TEX_COORD);
	error = glGetError();

	//�V�F�[�_�v���O�����������N
	m_pProgram->link();
	error = glGetError();

	//uniform�ϐ��̃��X�g��ۑ�
	m_pProgram->updateUniforms();
	error = glGetError();

	////uniform�ϐ��̔ԍ����擾
	//uniform_sampler = glGetUniformLocation(m_pProgram->getProgram(), "sampler");
	////�e�N�X�`���ǂݍ���
	//m_pTextuer = Director::getInstance()->getTextureCache()->addImage("ink.png");

	//uniform�ϊ��̔ԍ����擾
	uniform_wvp_matrix = glGetUniformLocation(m_pProgram->getProgram(),"u_wvp_matrix");

	counter = 0;

	Director::getInstance()->setClearColor(Color4F(0, 1, 0, 0));

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::draw(Renderer * renderer, const Mat4& transform, uint32_t flags)
{
	//���Z����
	//glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
	//glBlendFunc(GL_ONE, GL_ONE);

	//����������
	GL::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLenum error;
	//�w�肵���t���O�ɑΉ����鑮���C���f�B�b�N�X������L�����āA���͖����ɂ���
	/*GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR
		| GL::VERTEX_ATTRIB_FLAG_TEX_COORD);*/
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
	error = glGetError();
	//�V�F�[�_��L��������
	m_pProgram->use();
	error = glGetError();

	counter++;

	//�O�p�`��4���_���̍��W
	Vec3 pos[6];
	Vec4 color[6];
	Vec2 uv[6];
	const float x = 50.0f;
	const float y = 50.0f;
	//���W��1�_���ݒ�
	pos[0] = Vec3(-x, -y,0);
	pos[1] = Vec3(-x, y, 0);
	pos[2] = Vec3(x, -y, 0);
	//�O�p�`�Q��
	pos[3] = Vec3(-x, y, 0);
	pos[4] = Vec3(x, -y, 0);
	pos[5] = Vec3(x, y, 0);
	//
	//�J���[����_���ݒ�
	//color[0] = Vec3(0, 0, 0);//��
	//color[1] = Vec3(1, 0, 0);//��
	//color[2] = Vec3(0, 1, 0);//��
	//color[3] = Vec3(0, 0, 1);//��


	color[0] = Vec4(1, 0, 0, 1);
	color[1] = Vec4(1, 0, 0, 1);
	color[2] = Vec4(1, 0, 0, 1);
	color[3] = Vec4(1, 0, 0, 1);
	color[4] = Vec4(1, 0, 0, 1);
	color[5] = Vec4(1, 0, 0, 1);

	//�e�N�X�`�����W����_���ݒ�
	/*uv[0] = Vec2(0, 1);
	uv[1] = Vec2(0, 0);
	uv[2] = Vec2(1, 1);
	uv[3] = Vec2(1, 0);*/

	////�摜�𖈃t���[���ړ�(4-1 ���K���1)
	//uv[0] = Vec2(0 + counter / 120.0f, 1);
	//uv[1] = Vec2(0 + counter / 120.0f, 0);
	//uv[2] = Vec2(1 + counter / 120.0f, 1);
	//uv[3] = Vec2(0 + counter / 120.0f, 0);
	//uv[4] = Vec2(1 + counter / 120.0f, 1);
	//uv[5] = Vec2(1 + counter / 120.0f, 0);

	//���K���4-1 2
	uv[0] = Vec2(0, 1);
	uv[1] = Vec2(0, 0);
	uv[2] = Vec2(1, 1);
	uv[3] = Vec2(0, 0);
	uv[4] = Vec2(1, 1);
	uv[5] = Vec2(1, 0);

	

	
	//�w�肵�������C���f�B�b�N�X�ɁA�f�[�^���֘A�Â���
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, pos);

	//�w�肵�������C���f�B�b�N�X�ɁA�f�[�^���֘A�Â���
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);


	////�w�肵�������C���f�B�b�N�X�ɁA�f�[�^���֘A�Â���
	//glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, uv);


	Mat4 matWorld = Mat4::IDENTITY;

	//���[���h�r���[�v���W�F�N�V�����s��̍쐬
	static float yaw = 0.0f;
	//yaw += 0.01f;
	//120frm�ň��]
	yaw += CC_DEGREES_TO_RADIANS(3.0f);
	Mat4 matProjection;
	Mat4 matView;
	Mat4 matWVP;

	// �v���W�F�N�V�����s��i�ˉe�s��j���擾
	matProjection = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION); 

	//�r���[�s����擾
	matView = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	// �X�P�[�����O 
	Mat4 matScale;
	//�S�����ɔ{�̃X�P�[�����O�s��𐶐�
	//���K���4-2 3**********
	float scale =CC_DEGREES_TO_RADIANS(3.0f * counter);
	//���������W�A���Ƃ��ăT�C���֐�(6.28���炢�ň����)
	scale = sinf(scale);
	//***************************
	//Mat4::createScale(2.0f, 2.0f, 2.0f, & matScale);
	Mat4::createScale(Vec3(scale, scale, scale), &matScale);
	//��]
	Mat4 matRot;
	Mat4 matRotX, matRotY, matRotZ;
	//�e��������v�Z���A�Ō�ɍ���
	Mat4::createRotationZ(0, &matRotZ);
	Mat4::createRotationX(0, &matRotX);
	Mat4::createRotationY(yaw, &matRotY);
	//��]������
	matRot = matRotY * matRotX * matRotZ;

	//���s�ړ�
	Mat4 matTrans;
	//Mat4::createTranslation(3.14f, 3.14f, 3.14f, &matTrans);
	Mat4::createTranslation(Vec3 (1280.0f/2.0f, 720.0f/2.0f, 0.0f), &matTrans);

	//�X�P�[�����O�A��]�A���s�ړ�������
	//���[���h�s����v�Z
	matWorld = matTrans * matRot * matScale;

	//WVP�s�������
	matWVP = matProjection * matView * matWorld;

	//�E������\���x�N�g��
	Vec3 v1(1, 0, 0);
	matWorld.transformVector(&v1);

	
	//��������WVP�s����V�F�[�_�ɑ���
	glUniformMatrix4fv(uniform_wvp_matrix, 1, GL_FALSE, matWVP.m);


	//�w�肵��uniform�ϐ��Ƀe�N�X�`�����֘A����
	/*glUniform1i(uniform_sampler, 0);
	GL::bindTexture2D(m_pTextuer->getName());*/

	//4���_���̃f�[�^�ŎO�p�`��`�悷��
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

	////�l�p�`�̕`��
	//pos[0].x += 0.1f; pos[0].y += 0.1f;
	//pos[1].x += 0.1f; pos[1].y += 0.1f;
	//pos[2].x += 0.1f; pos[2].y += 0.1f;
	//pos[3].x += 0.1f; pos[3].y += 0.1f;

	//color[0] = Vec4(0, 0, 1, 0.5f);
	//color[1] = Vec4(0, 0, 1, 0.5f);
	//color[2] = Vec4(0, 0, 1, 0.5f);
	//color[3] = Vec4(0, 0, 1, 0.5f);

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	error = glGetError();
}
