# focus_timer

作業に集中するための、シンプルな25分カウントダウンタイマーです。
C++ と Qt Widgets で作成した Windows 向けデスクトップアプリです。

<!-- スクリーンショットを撮ったら docs/screenshot.png に置いて、下の行の先頭の <!-- と末尾の --> を消してください -->
[アプリ画面](.\docs\screenshot.png) 

## 主な機能

- 25分からのカウントダウン表示（`MM:SS` 形式）
- スタート／一時停止／再開
- リセット
- 時間になったら完了メッセージを表示

## 使用技術

| 項目 | 内容 |
| --- | --- |
| 言語 | C++ |
| GUIフレームワーク | Qt 6.12（Qt Widgets） |
| ビルドシステム | CMake |
| コンパイラ | MinGW 13.1.0 64-bit |
| 開発環境 | Qt Creator / VS Code |
| 対応OS | Windows |

## ビルド方法

### Qt Creator を使う場合

1. Qt 6（MinGW 64-bit）と Qt Creator をインストールする
2. Qt Creator で `CMakeLists.txt` を開く
3. キット「Desktop Qt 6.x MinGW 64-bit」を選択する
4. 実行ボタン（▷）でビルドして起動する

### コマンドラインの場合

Qt と MinGW のパスを環境に合わせて指定してください。

```bash
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=C:/Qt/6.12.0/mingw_64
cmake --build build
```

## 設計のポイント

- 画面は `.ui` ファイルを使わず、コードでレイアウトを組み立てています（`QVBoxLayout` / `QHBoxLayout`）
- `QTimer` で1秒ごとにシグナルを発生させ、残り秒数はアプリ側の変数で管理しています
- ボタン操作とタイマーの処理は、Qt のシグナル／スロットで接続しています
- ウィジェットに親を指定し、Qt の親子関係によるメモリ管理を利用しています

## 今後の予定

- [ ] 作業25分／休憩5分の自動切り替え
- [ ] 作業記録のファイル保存
- [ ] 今日・今週の合計作業時間の表示
- [ ] 時間を変更できる設定画面
- [ ] タスクトレイ常駐と通知
- [ ] ユニットテストと GitHub Actions による自動ビルド

## 作者

[shinchan2525](https://github.com/shinchan2525)
