# MyStudy/.../DirectVertexHunting/VertexHunting (アーカイブ: 2022-2023年の最古プロトタイプ群)

DVH開発の最も初期段階にあたるC++プロトタイプ群(2022-2023年)。vertexファイルの後処理・
分類、shifterとbasetrackのマッチング、BG study用のtrackシャッフルなど、周辺ツールが
中心。後の `I:\NINJA\E71a\work\kasumi\work\File`、
`I:\NINJA\E71a\work\kasumi\DVH`、
`I:\NINJA\E71a\work\kasumi\ECC5\Direct_vertex_hunting` に引き継がれた。
本フォルダでは現在開発を行っておらず、履歴保存用に記録している。

## BG study (track shuffle)

| プログラム | 入出力 | 役割 |
|---|---|---|
| `shuffle_stop_track_position` | `input output output_folder_path` | stop track位置をシャッフル(BG study用。DVHの`ShuffleTrackDataForBGstudy`の前身) |
| `shuffle_take_into_account_track_density_by_place` | `input input_filmsize output_folder times_of_shuffle mode(0:5分割/1:メッシュ) mode1(stop:0/start:1)` | 場所ごとのtrack密度を考慮したシャッフル |

## vertexファイルの後処理・分類

| プログラム | 入出力 | 役割 |
|---|---|---|
| `add_bwd_blk_flg` | `input-vertex-file output` | backward blockフラグを付加 |
| `add_flg_for_classification` | `input-vertex-file output` | 分類用フラグを付加 |
| `calcurate_coplanarity_angle` | `input-vertex-file output` | coplanarity角度を計算 |
| `count_each_event` | `input-vertex-file output` | イベント毎のカウント |
| `output_event_chain_list` | `input-vertex-file list` | chainリストを出力 |
| `output_event_infomation` / `output_from_fdata` | `input-vertex-file output mode(0:event/1:2vtx/2:track/3:epair)` | イベント情報を出力(2系統で同趣旨) |
| `kink_angle_check` | `in output_file` | kink角度のチェック |
| `remove_epair` | `input_file list output_file` | e+e-ペアの除去 |

## shifter / basetrack マッチング

| プログラム | 入出力 | 役割 |
|---|---|---|
| `shifter_id_matching` / `shifter_id_matching_with_muonflg` | `shifter-basetrack.txt list.txt output_file` | shifter IDとbasetrackのマッチング(muonフラグ有無の2系統) |
| `matching_shifter_basetrack` | `input_file list output_file` | 同種のshifter/basetrackマッチング |
| `add_eccflg_to_,muon` | `muon.txt list_auto.txt list_manual.txt output_file` | ECCフラグをmuonリストに付加 |
| `add_OSSbastrackinfo_to_sharingfile` | `in_sharingfile in_oss output_file mode` (mode1: add oss info) | OSS basetrack情報をsharing fileに付加 |
| `add_OSSbastrackinfo_to_sharingfile1` | `in_sharingfile stop_list output_file` | 同上の別バージョン |
| `analysis_viewercheck_connected_track` | `connect_list.txt muon.all output_file.txt times` | viewerチェックでの接続track解析 |
| `check_timestamp` | `input_file list output_file` | タイムスタンプの確認 |

## その他

| プログラム | 入出力 | 役割 |
|---|---|---|
| `get_film_size` | `input(stop.txt) output(pl,xmin,xmax,ymin,ymax,z) mode(0:stop/1:start)` | フィルムの範囲(サイズ)を取得 |
| `count_mid` (`count_muid.cpp`) | `input_file list output_file` | muon ID毎のカウント |
| `VertexHunting` | - | ソースファイルなし。ソリューション名を冠したプレースホルダープロジェクト |
| `ztmp`, `zzz_for_test` | - | 動作確認・一時テスト用 |

## ビルド

Visual Studio ソリューション `VertexHunting.sln`。他世代と同様 `FILE_structure`,
`functions`, `VxxReader` 等の共通ライブラリに依存する(本リポジトリ外)。
