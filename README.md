# opencv3mixing
The ROS package to develop and test OpenCV3.
頑張れ CIR-KIT 2017年度生！


質問などあったら上の方にある issue から @yasu80 とか, コラボレータになってる人に聞いてくれていいのよ<br>
新たな知見などあったらwikiに追記してくれると嬉しい

# 開発段階のガイド

## 1. 色検出

開発環境における簡単な色検出を行い, 検出したターゲットのポイント(重心点)をパブリッシュします.
または, 二値化した画像をパブリッシュします.

### 具体例

Issue [#12](https://github.com/CIRKIT-ARC-1stGrade/opencv3mixing/issues/12) に示した画像の精度試験.
ヒント：
 - 画像の色要素(HSVにせよBGRにせよ)の閾値を範囲で指定する関数.
 - 画像のMat構造体のどこに色要素があるかを確認.
 - 画像のハシからハシまでを検査し尽くす方法は.
 - ノイズ処理はどうか.

複数の答えが考えられるから、いろいろ試して精度の高い方法を割り出してね

## 2. 形状検出

開発環境における簡単な形状検出を行い, 検出したターゲットのポイント(重心点)をパブリッシュします.
または, ボーンの代表点としてパブリッシュします.

ヒント:
 - 画像の勾配を抜き出す方法(一定以上の値を取る・取らないで二値化)
 - 特徴量を検出する方法

## 3. 要素を統合しての検出

開発環境において複合要素による, 複合要素を持つ一般物体を検出します.

※人間の形状は決め打ちのハードコーディングにするには複雑すぎると思われますので, 分類器(分類データ)を借りててくるか強化学習を用いた手法を用いることになるかもしれません
しかしこのような場合でも, 上記の手法を用いることは可能です.

### 参考
- [公式サンプル](http://opencv.jp/sample/object_detection.html)
- [haarCascadeClassifier:顔認識によく使う分類器についての解説](http://docs.opencv.org/2.4/modules/objdetect/doc/cascade_classification.html)
- [日本語の解説ページ:qiita](http://qiita.com/nonbiri15/items/c8e666c4964d09ace652)
- [OpenCV 2.2 リファレンス](http://opencv.jp/opencv-2svn/cpp/)
- これからの強化学習:[図書館](https://www.lib.kyutech.ac.jp/opac/volume/769623?current=1&locale=ja&q=これからの強化学習&target=l&total=1&trans_url=https%3A%2F%2Fwww.lib.kyutech.ac.jp%2Fopac%2Fhome%2Fresult%2Fja%3Fq%3D%25E3%2581%2593%25E3%2582%258C%25E3%2581%258B%25E3%2582%2589%25E3%2581%25AE%25E5%25BC%25B7%25E5%258C%2596%25E5%25AD%25A6%25E7%25BF%2592%26target%3Dl)　ISBN-10: 4627880316 どうやって強化学習が「特をする」相関関係を見つけていくかの数理が示されます:ロボット応用の話もあるよ

## 4. 最適化
システムは実行環境(本番環境)において最適な速度を保つことが要求されます.
