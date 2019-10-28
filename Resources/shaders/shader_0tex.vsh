attribute vec4 a_position;//座標
attribute vec4 a_color; //(入力)色
varying vec4 v_color; //(出力)色

void main() {
	gl_Position = a_position;	//シェーダの出力に座標をコピー
	v_color = a_color;		//入力から出力に色をコピー
}