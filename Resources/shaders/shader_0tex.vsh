attribute vec4 a_position;//���W
attribute vec4 a_color; //(����)�F

uniform mat4 u_wvp_matrix;//(����)���[���h,�r���[,�v���W�F�N�V�����s��

varying vec4 v_color; //(�o��)�F


void main() {
	//���͍��W�����[���h, �r���[, �v���W�F�N�V����(�ˉe)�ϊ�
	gl_Position = u_wvp_matrix * a_position;
	v_color = a_color;		//���͂���o�͂ɐF���R�s�[
}