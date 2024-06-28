# CUB3D
Ray casting 을 이용한 3D 가상 환경에서 오버워치의 트레이서를 구현

## 플레이 영상
https://youtu.be/1z1isaN8vTw?feature=shared

## 사용법

```
./cub3D map/<map_name>
```
- map_name 에 .cub 맵 파일을 입력
- 2 종류의 map 존재
  - mandatory
    - src 로 시작하는 mandatory 전용 맵
    - 천장과 바닥의 단색으로 명시
  - bonus
    - bon 으로 시작하는 bonus 전용 맵
    - 천장과 바닥이 texture 경로로 명시

## 게임 조작

- 이동 조작
    - W : 앞으로 이동 (두 번 누르면 달리기)
    - S : 뒤로 이동
    - A : 왼쪽으로 이동
    - D : 오른쪽으로 이동
    - space : 점프
    - 마우스 이동 : 시선 및 에임 조정

- 공격 조작      
    - 마우스 좌클릭 : 펄스 피스톨 발사 (마우스 휠 클릭도 가능) 
    - V : 근접 공격
      
- 스킬 조작
    - shift : 블링크 (Blink)
    - E or 마우스 우클릭 : 리콜 (Recall)
          
- 기타 조작
    - ctrl : 앉기 
    - R : 재장전
    - 마우스 휠 조작 : 미니맵 크기 변경 (위로 굴리면 확대, 아래로 굴리면 축소)
    - 1 : 마우스 바인딩 on/off

