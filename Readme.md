# CUB3D
Ray casting 을 이용한 3D 가상 환경에서 오버워치의 트레이서를 구현 (feat. mlx)

<img width="1924" alt="image" src="https://github.com/seonjo1/CUB3D/assets/127729846/f11f0ad1-0fec-438c-9001-4bce65ae47a3">


## 플레이 영상
https://youtu.be/1z1isaN8vTw?feature=shared

## 실행 방법

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

- **이동 조작**
    - W : 앞으로 이동 (두 번 누르면 달리기)
    - S : 뒤로 이동
    - A : 왼쪽으로 이동
    - D : 오른쪽으로 이동
    - space : 점프
    - 마우스 이동 : 시선 및 에임 조정

- **공격 조작**     
    - 마우스 좌클릭 : 펄스 피스톨 발사 (마우스 휠 클릭도 가능) 
    - V : 근접 공격
      
- **스킬 조작**
    - shift : 블링크 (Blink)
    - E or 마우스 우클릭 : 리콜 (Recall)
          
- **기타 조작**
    - ctrl : 앉기 
    - R : 재장전
    - 마우스 휠 조작 : 미니맵 크기 변경 (위로 굴리면 확대, 아래로 굴리면 축소)
    - 1 : 마우스 바인딩 on/off

# map 형식

<img width="422" alt="스크린샷 2024-06-28 오후 3 57 54" src="https://github.com/seonjo1/CUB3D/assets/127729846/a3c51f98-9b2b-4f47-9ca1-bf92a8db77f9">

- **텍스처**
  - NO : 북쪽 벽 텍스처 경로
  - SO : 남쪽 벽 텍스처 경로
  - WE : 서쪽 벽 텍스처 경로
  - EA : 동쪽 벽 텍스처 경로
  - CT : 천장 텍스처 경로
  - FT : 바닥 텍스처 경로

- **map**
  - N, S, W, E : 플레이어 위치 및 방향
  - 1 : 벽
  - 0 : 빈 공간 


# 구현 리스트
- 플레이어의 다양한 움직임 구현
- 오버워치 트레이서 스킬 구현
- 애니메이션 스프라이트 적용
- 벽 충돌 구현
- 미니맵 구현
- 레이 캐스팅으로 벽 구현
- 벽과 바닥에 텍스처 적용
- skybox 구현

# build

```
make
```

- 최소한의 기능만 적용된 mandatory cub3D 생성

```
make bonus
```

- 모든 기능이 적용된 bonus cub3D 생성

```
make clean
```

- 실행파일 만드는데 생성된 .o 파일들 제거

```
make fclean
```

- make clean + cub3D 삭제

```
make re
```

- make fclean + make

---

<img width="207" alt="스크린샷 2024-06-28 오후 4 13 02" src="https://github.com/seonjo1/CUB3D/assets/127729846/45798e1e-b50d-4bc0-ac83-37a4217265e1">
