attribute vec4 a_position;//座標
attribute vec4 a_color; //(入力)色

uniform mat4 u_wvp_matrix;//(入力)ワールド,ビュー,プロジェクション行列

varying vec4 v_color; //(出力)色


void main() {
	//入力座標をワールド, ビュー, プロジェクション(射影)変換
	gl_Position = u_wvp_matrix * a_position;
	v_color = a_color;		//入力から出力に色をコピー
}