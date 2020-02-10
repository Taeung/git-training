from sys import stdin


def find_min(light, cost, pos, son):
    if pos < len(light) and (light[pos] - son)*cost[pos] > (son - light[pos - 1])*cost[pos - 1]:
        return pos
    return pos -1

n = int(stdin.readline())
m = int(stdin.readline()) # 손흥민 위치
ans = 0
dist = 0
light = list(map(int, stdin.readline().split()))
cost = list(map(int, stdin.readline().split()))

for i in range(n):
    pos = 0
    while True:
        if pos >= len(light) or light[pos] > m:
            break
        pos += 1
    pos = find_min(light, cost, pos, m)
    dist += abs(light[pos]-m)
    ans += dist*cost[pos]
    m = light[pos]
    light.pop(pos)
    cost.pop(pos)

print(ans)
