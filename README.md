# DiceCardGame
==============================================
添付ファイル一覧
==============================================

　・Game.exe	ゲーム実行ファイル
　・/CSV			CSVファイルフォルダ
　・/img			画像ファイルフォルダ
　・/source		ソースファイルフォルダ

==============================================
利用方法
==============================================

Game.exeからゲームを起動してください

==============================================
利用方法
==============================================

◆操作方法
-全般-
　キーボード操作
　・Xキー		メニュー表示/非表示
　・SPACEキー		決定

-バトル-
　キーボード操作
　・SPACEキー		攻撃

-新規カード作成-
　キーボード操作
　・キャラ名、キャラ画像、技名を入力する際に使用

　マウス操作
　・左クリック		各要素を編集する際に各ボタンをクリック

-カードリスト-
　キーボード操作
　・↑↓キー		カードの選択
　・←→キー		メニュー内容の選択

==============================================
遊び方
==============================================

オリジナルのカードでバトルができます。
バトルは完全ランダム行動です。バトエンのような感覚で遊びます。

オリジナルのカードを作ることができます。
キャラ名、キャラ画像、HP、技名、技威力、技種類を決定し、保存することでオリジナルカードが完成します。
技の種類と詳細は以下の通りです
・攻撃：通常攻撃です。相手にダメージを与えます。
・強化：自身が使う攻撃、溜めで与えるダメージが永続で増加します。
・弱化：相手が使う攻撃、溜めで与えるダメージが永続で減少します。
・回復：自身のHPを回復します。最大HPを超えることはありません。
・溜め：溜め攻撃です。2回連続で同じ数字を出す必要があるため1/6で成功、5/6で失敗になります。
　　　　強化の増加量が通常攻撃の4倍になるロマン技です。

オリジナルカードはHP及び6つの技に割り振れるポイント数が最大で1000になっています。
各要素にどの程度ポイントを割り振るか、遊び手の個性が現れるゲームだと考えています。

キャラ画像はimgフォルダに格納してください。
画像は強制的に150*150pixelの正方形として表示されます。縦横比が1：1でない画像は圧縮されて表示されるため、あらかじめ画像サイズの変更をしておくことを推奨します。

バトルに使用するカードはカードリストから好きなカードを選択しセットすることができます。


==============================================
動作確認環境
==============================================

Windows11


==============================================
開発ライブラリ　（以下、原文）
==============================================

著作権等

<<一般的な事項>>
　・ＤＸライブラリの著作権は山田 巧が保持します。

　・無料ソフト、有料ソフト問わず、ＤＸライブラリを使用して作成されたソフトウエアに対する
　　ライセンス料等は(商用利用・法人利用問わず)一切発生しません。

　・ＤＸライブラリを用いたことによって生じた如何なる損害に対しても著作権保有者はその
　　保障義務を一切負わないものとします。

　・著作権保有者はＤＸライブラリに不備が有っても、それを訂正する義務を負いません。

　・ＤＸライブラリを使用して作成されたソフトウエアにＤＸライブラリを使用した旨を記載する
　　必要はありません。(記載されれば嬉しいですが)

　・ＤＸライブラリが使用している各ライブラリについて、配布するソフトウエアのドキュメント等に
　　下記の著作権表記を含めてください。

　　　libjpeg　Copyright (C) 1991-2013, Thomas G. Lane, Guido Vollbeding.
　　　this software is based in part on the work of the Independent JPEG Group


　　　libpng　Copyright (C) 2004, 2006-2012 Glenn Randers-Pehrson.
　　　zlib　Copyright (C) 1995-2012 Jean-loup Gailly and Mark Adler.


　　　libtiff　Copyright (c) 1988-1997 Sam Leffler
　　　libtiff　Copyright (c) 1991-1997 Silicon Graphics, Inc.

　　　Permission to use, copy, modify, distribute, and sell this software and
　　　its documentation for any purpose is hereby granted without fee, provided
　　　that (i) the above copyright notices and this permission notice appear in
　　　all copies of the software and related documentation, and (ii) the names of
　　　Sam Leffler and Silicon Graphics may not be used in any advertising or
　　　publicity relating to the software without the specific, prior written
　　　permission of Sam Leffler and Silicon Graphics.

　　　THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
　　　EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
　　　WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

　　　IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
　　　ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
　　　OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
　　　WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
　　　LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
　　　OF THIS SOFTWARE.


　　　libogg　Copyright (C) 2002-2009 Xiph.org Foundation

　　　Redistribution and use in source and binary forms, with or without
　　　modification, are permitted provided that the following conditions
　　　are met:

　　　- Redistributions of source code must retain the above copyright
　　　notice, this list of conditions and the following disclaimer.

　　　- Redistributions in binary form must reproduce the above copyright
　　　notice, this list of conditions and the following disclaimer in the
　　　documentation and/or other materials provided with the distribution.

　　　- Neither the name of the Xiph.org Foundation nor the names of its
　　　contributors may be used to endorse or promote products derived from
　　　this software without specific prior written permission.

　　　THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
　　　``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
　　　LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
　　　A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION
　　　OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
　　　SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
　　　LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
　　　DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
　　　THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
　　　(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
　　　OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


　　　Opus audio codec
　　　Copyright 2001-2011 Xiph.Org, Skype Limited, Octasic,
　　　 Jean-Marc Valin, Timothy B. Terriberry,
　　　 CSIRO, Gregory Maxwell, Mark Borgerding,
　　　 Erik de Castro Lopo

　　　Redistribution and use in source and binary forms, with or without
　　　modification, are permitted provided that the following conditions
　　　are met:

　　　- Redistributions of source code must retain the above copyright
　　　notice, this list of conditions and the following disclaimer.

　　　- Redistributions in binary form must reproduce the above copyright
　　　notice, this list of conditions and the following disclaimer in the
　　　documentation and/or other materials provided with the distribution.

　　　- Neither the name of Internet Society, IETF or IETF Trust, nor the
　　　names of specific contributors, may be used to endorse or promote
　　　products derived from this software without specific prior written
　　　permission.

　　　THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
　　　``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
　　　LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
　　　A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
　　　OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
　　　EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
　　　PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
　　　PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
　　　LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
　　　NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
　　　SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


　　　Opusfile
　　　Copyright (c) 1994-2013 Xiph.Org Foundation and contributors

　　　Redistribution and use in source and binary forms, with or without
　　　modification, are permitted provided that the following conditions
　　　are met:

　　　- Redistributions of source code must retain the above copyright
　　　notice, this list of conditions and the following disclaimer.

　　　- Redistributions in binary form must reproduce the above copyright
　　　notice, this list of conditions and the following disclaimer in the
　　　documentation and/or other materials provided with the distribution.

　　　- Neither the name of the Xiph.Org Foundation nor the names of its
　　　contributors may be used to endorse or promote products derived from
　　　this software without specific prior written permission.

　　　THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
　　　``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
　　　LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
　　　A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION
　　　OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
　　　SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
　　　LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
　　　DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
　　　THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
　　　(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
　　　OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


　　　Mersenne Twister
　　　Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
　　　All rights reserved.

　　　Redistribution and use in source and binary forms, with or without
　　　modification, are permitted provided that the following conditions
　　　are met:

　　　1. Redistributions of source code must retain the above copyright
　　　notice, this list of conditions and the following disclaimer.

　　　2. Redistributions in binary form must reproduce the above copyright
　　　notice, this list of conditions and the following disclaimer in the
　　　documentation and/or other materials provided with the distribution.

　　　3. The name of the author may not be used to endorse or promote products
　　　derived from this software without specific prior written permission.

　　　THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
　　　IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
　　　OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
　　　IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
　　　INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
　　　NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
　　　DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
　　　THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
　　　(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
　　　THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


　　　Bullet　Copyright (c) 2003-2006 Erwin Coumans.
