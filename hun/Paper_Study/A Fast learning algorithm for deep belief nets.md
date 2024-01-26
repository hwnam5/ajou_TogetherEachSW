저자 : Geoffrey E. Hinton and Simon Osindero

# Abstract
- hidden layer가 많고 densely-connected belief nets에서 추론을 어렵게 만드는 설명 효과를 제거하기 위해 "complementary priors"를 사용하는 방법을 보여준다.
- "complementary priors"를 사용하면 두 layer가 undirected associative memory를 형성하는 경우, 더 빠르고 greedy한 알고리즘을 도출할 수 있다.

### DBN(Deep Belief Network) & RBM(Restricted Boltzmann Machine)
#### RBM
- RBM은 Generative Model로 ANN, DNN, CNN, RNN 과 같은 Deterministic Model들과 다른 목표를 가짐.
- Deterministic Model들이 타겟과 가설 간의 차이를 줄여서 오차를 줄이는 것이 목표라고 한다면, Generative Model들의 목표는 확률밀도함수를 모델링하는 것이다.
- Boltzmann Machine이 가정한 것은 "우리가 보고 있는 것들 외에도 보이지 않는 요소들까지 잘 포함시켜 학습할 수 있다면 확률분포를 좀 더 정확하게 알 수 있지 않을까?"라는 것이다.
- <img src = "Pasted image 20240105220348.png">
- 노란색은 hidden unit, 초록색은 visible unit.
- RBM은 Boltzmann Machine에서부터 파생되어 나온 것으로 visible unit과 hidden unit에는 내부적인 연결이 없고, visible unit과 hidden unit 간의 연결만이 남아있는 형태이다.
- 우선은 visible, hidden layer의 node 간의 내부적인 연결이 없어진 것은 사건 간의 독립성을 가정함으로써 확률분포의 결합을 쉽게 표현하기 위해서이다.
- 또, visible layer와 hidden layer만을 연결해줌으로써 visible layer의 데이터가 주어졌을 때 hidden layer의 데이터를 계산할 수 있도록 하거나 혹은 hidden layer의 데이터가 주어졌을 때 visible layer의 데이터를 계산할 수 있도록 하는 ‘조건부 확률’을 계산할 수 있게 하는 것이다.
- 즉, $p(h,v)$ 는 계산하기 어렵지만, $p(h|v)$ 나 $p(v|h)$ 는 계산이 수월하기 때문이다.
- 더 자세한 내용 : https://angeloyeo.github.io/2020/10/02/RBM.html

#### DBN
- 입력층과 은닉층으로 구성된 RBM을 블록처럼 여러 층으로 쌓인 형태로 연결된 신경망
- 피드포워드 신경망에서 경사감소 소멸문제를 해결하기 위해 등장
- 특징
	- 비지도학습
	- 데이터가 충분하지 않을 때 유용
	- 겹층 RBM
- <img src="Pasted image 20240105221225.png">

# 1. Introduction
- 데이터 벡터가 주어졌을 때 숨겨진 활동의 조건부 분포를 추론하기 어렵기 때문에 hidden layer가 많은 조밀하게 연결된 방향성 신뢰 네트워크에서는 학습이 어렵다. 
- Variational methods : 실제 조건부 분포에 대한 근사치를 사용. but, 사전 분포가 독립성을 가정하는 가장 깊은 hidden layer에서는 근사치가 좋지 않을 수 있다.
- Variational learning : 모든 매개변수를 학습해야 하며 매개변수 수가 증가함에 따라 학습 시간 규모가 제대로 설정되지 않을 수 있다.
- 그래서 이 논문에서는 새로운 모델을 설명하려고 함.
	- 상위 두 개의 hidden layer가 undirected associative memory를 형성.
	- 나머지 hidden layer가 directed acyclic graph를 형성.(이미지의 픽셀과 같은 관찰 가능한 변수로 변환)
- 이 모델의 특징
	1. 수백만의 매개변수와 hidden layer가 있어도 좋은 매개변수 세트를 빠르게 찾을 수 있는 빠르고 greedy한 algorithm이 있다.
	2. 비지도 방식이지만, 레이블과 데이터를 모드 생성하는 모델을 학습해 레이블이 지정된 데이터에도 적용할 수 있다.
	3. MNIST에서 우수한 성과가 있는 미세 조정 알고리즘이 있다.
	4. 생성모델을 사용하면 깊은 hidden layer의 분산 표현을 쉽게 해석할 수 있다.
	5. 지각을 형성하는데 필요한 추론은 빠르고 정확하다.
	6. 학습 알고리즘은 지역적으로, 시냅스 강도 조정은 시냅스 전, 후의 상태에만 의존한다.
	7. 통신이 간단하다. 뉴런은 확률론적 이진 상태만 전달하면 된다.

- 이후 섹션에 대해 소개함.
- section 2 
	- 지향 모델에서 추론을 어렵게 만드는 보완적 사전 개념(idea of complementary prior)을 소개한다. 
	- 상호보완적인 사전확률을 갖는 direct belief network의 예가 제시됨.
- section 3 
	- RBM와 가중치가 묶인 무한 directed network간의 동등성을 보여준다.
- section 4 
	- 한번에 한 레이어씩 다층 지향 네트워크를 구성하기 위한 빠르고 greedy한 알고리즘을 소개한다. 
	- variational bound를 사용하면 각 새로운 레이터가 추가될 때 전체 생성 모델이 향상된다는 것을 알 수 있다. 
	- greedy 알고리즘은 동일한 "약한" 학습기를 반복적으로 사용하는 부스팅과 어느 정도 유사, 다음 단계에서 새로운 것을 학습할 수 있도록 각 데이터 벡터에 다시 가중치를 부여하는 대신 이를 다시 나타냄.(?)
	- Deep Directed Net을 구성하는 데 사용되는 "약한" 학습기는 그 자체가 undirected graphical 모델임.(?)
- section 5 
	- Fast Greedy 알고리즘에 의해 생성된 가중치가 up-down 알고리즘을 사용해 미세 조정될 수 있는 방법을 보여준다.
- section 6 
	- MNIST에서 성능 비교
	- support vector machines에서 성능 비교
- section 7 
	- 시각적 입력 제약 없이 네트워크가 실행될 때 네트워크가 어떻게 동작하는지 설명한다.
- + 이 논문에서는 확률론적 이진 변수로 구성된 네트워크를 고려할 것이지만 변수의 로그 확률이 직접 연결된 이웃 상태의 추가 함수인 다른 모델로 아이디어를 일반화할 수 있다고 한다.

# 2. Complementary priors
- Figure 2(Explaining away효과)
	- <img src="Pasted image 20240118172340.png">
	- C : 암에 걸림, H : 두통 있음, B : 멍이 듦.
	- $P(C|H)$ : 두통이 있을 때 암에 걸렸을 확률 = 0.5525
	- $P(C|H, B)$ : 두통과 멍이 있을 때 암에 결렸을 확률 = 0.112
	- 이 상황에서 두통이 있으면 암에 걸렸을 확률이 55.25%이다. 그런데 거울을 보고 멍이 들었음을 알게 되었다면 암에 걸렸을 확률이 11.2%로 감소한다.
	- 멍이 들었다.(B)라는 사건은 두통이 '암' 이 아니라 '싸움'이라는 또 다른 원인으로 인해 발생했을 수 있다는 사실을 설명하기 때문이다.
	- 이와 같이 Explaining away 효과가 발생할 경우 서로 독립인 변수 '싸움'과 '암'이 서로 영향을 미치기 때문에 추론이 어려워진다.
- directed belief nets에서 Explaining away 현상은 추론을 어렵게 만든다.
- 조밀하게 연결된 네트워크에서 hidden variable에 대한 posterior distribution(사후 분포)는 혼합 모델이나 additive Gaussian noise가 있는 선형 모델을 제외하고는 다루기 어렵다.
- MCMC(Markov Chain Monte Carlo)방법을 사용해 후방에서 샘플링할 수 있지만 시간이 오래 걸린다.
	- MCMC(Markov Chain Monte Carlo) : 
		- Markov Chain을 이용한 Monte Carlo 방법.
		- Monte Carlo : 수식만으로는 계산하기 어려운 문제가 있을 때 랜덤 샘플을 얻은 뒤 그 랜덤 샘플을 이용해서 함수의 값을 확률적으로 계산하는 방법이다.
		- Markov Chain : 미래 확률이 과거 확률에 독립이며 오로지 직전 시점의 확률에만 의존한다는 것이 핵심이다. 즉, 한 상태에서 다른 상태로의 전이(transition)은 그동안의 전이 확률(**Transition Probability**)을 필요로 하지 않고 바로 직전의 전이 확률로 추정할 수 있다는 얘기이다.
		- MCMC : MCMC는 우리가 샘플을 얻고자 하는 목표 분포인 Stationary distribution으로부터 랜덤 샘플을 얻는 방법
	- https://m.blog.naver.com/jinis_stat/221687056797
- Variational methods(Neal and Hinton, 1998)은 실제 사후를 근사화하며 훈련 데이터의 로그 확률에 대한 하한을 향상시키는데 사용할 수 있다. hidden state에 대한 추론이 잘못 수행된 경우에도 학습이 변이 범위를 개선한다는 장점이 있지만, hidden variable이 있는 모델에서도 설명을 완전히 제거하는 방법을 찾는 것이 낫다. 그런데 이는 불가능하다는 것이 널리 알려져 있다.

- Logistic belief net :
- <img src="Pasted image 20240125133037.png">
- 위 그래프는 logistic function. Logistic belief net은 logistic함수를 기반으로 한 확률적 그래픽 모델.
##  $p(s_{i} = 1) = \frac{1}{1 + exp(-b_{i} - \sum s_{i}w_{ij})}$  
- bi : i의 편향, wij : i에서 j로의 가중치, i:해당노드, j:부모노드
- 노드 i가 켜질(turn on) 확률은 위 수식처럼 부모 노드 j의 켜짐 여부와 연결 가중치를 이용한 함수로 표현된다.
- 만약 logistic belief net이 하나의 은닉층만을 가진다면 은닉 노드들이 서로 독립적으로 선택되기 때문에 prior distribution이 독립 분포로 표현이 가능.
- 하지만 posterior distribution은 비독립적인데, 이는 데이터로부터의 likelihood 로 인해 생긴다.
- 연구진은 별도의 은닉층을 추가해 이 likelihood와 완전히 정반대의 상관관계를 갖는 complementary prior를 생성함으로써 첫번째 은닉층에서 발생하는 explaining away 효과를 제거할 수 있음을 보였다.
- 이후 likelihood와 prior의 곱으로 결합 분포를 구하고, 이를 normalization constant로 나누어 posterior를 독립 분포로 표현할 수 있다
- Complementary prior가 항상 존재한다고 확신할 수는 없지만, 다음 항목에서 소개하듯이 모든 은닉층에서 짝지어진 가중치들이 complementary prior를 생성하는 무한한 logistic belief net의 간단한 예시가 있음.

### Figure 3
- <img src="Pasted image 20240125134316.png" height="300">
- downward : generative model.
- upward : 모델의 일부가 아님. V를 고정할 때, 사후 분포로부터 샘플을 추론하는데 사용되는 매개변수.
### Appendix A : Complementary Priors
#### General complementarity
- x : 관찰 가능한 변수, y : hidden 변수. 에 대한 분포를 생각할 때,
- 주어진 우도 함수 $P(x|y)$ 에 대해 대응하는 상보적(complementary) 사전 분포는 $P(y)$ 로 정의됨. (이하 베이즈 정리 사용됨)
- $P(y|x)$ : 사후 분포
	1. 이에 대한 결합 분포 $P(x, y) = P(x|y)P(y)$ .
	2. $P(y|x) = \frac{P(x|y)P(y)}{P(x)}$ . (조건부확률에 의해)
	3. $P(y|x) \propto P(x|y)P(y)$ .
	4. 1,2,3에 의해 결합분포($P(x, y)$)는 우도 함수($P(y|x)$)와 prior($P(x)$)의 곱으로 표현됨. 
	5. 결합분포($P(x, y)$)와 우도 함수($P(y|x)$)는 종속적.
- 다른 방식으로 $P(y|x)$ 를 표현 가능.
	- $P(y|x) =\Pi_{j}P(y_{j}|x)$ .
	- 이렇게 표현하면 독립적으로 $P(y|x)$ 사용 가능.
- 주의할 점 : 가능한 모든 함수형태가 보완적 사전확률을 허용하는 것은 아님.

## 2.1 An infinite directed model with tied weights
- Figure 3의 모델은 무한히 깊은 은닉층에서 무작위 구성으로 시작해, 활성화된 부모 노드가 베르누이 분포를 따라 특정 자식 노드를 활성화시키는 top-down 방식으로 데이터를 생성해낸다.
- 이 모델은 다른 direct network와는 다르게 가시층($V_{0}$)의 데이터 벡터($v^{0}_{i}$)로부터 시작해, 전치 가중치 행렬($W^{T}$)을 이용해 각 은닉층의 독립 분포를 차례대로 유추함으로써 모든 은닉층의 실제 posterior를 구할 수 있다.
- 이제 실제 posterior로부터 샘플을 만들어내 그것이 데이터와 얼마나 다른지를 계산할 수 있기 때문에 데이터 $V^{0}$ 로그 확률의 미분값을 계산할 수 있다.
- 먼저 $w^{00}_{ij}$ 에 대한 미분값을 구하면 다음과 같다.
	-  $w^{00}_{ij}$ : 은닉층 $H_{0}$ 의 j 유닛과 가시층 $V_{0}$의 i 유닛 간의 가중치
##  $\frac{\partial logp(V^{0})}{\partial w^{00}_{ij}} = <h^{0}_{j}(v^{0}_{i} - \hat{v}^{0}_{i})>$
- < ... > 는 샘플랭된 값들의 평균을 의미, $\hat{v}^{0}_{i}$ 는 가시 벡터 $v^{0}_{i}$ 가 샘플링된 은닉층으로부터 재생성되었을때 유닛 i가 켜져 있을 확률을 뜻한다.
- 만약 $\hat{v}^{0}_{i}$ 과 $v^{0}_{i}$ 가 같다면 샘플링된 은닉층으로부터 실제 가시 벡터를 완벽하게 재생성할 수 있다는 것을 뜻하며 이를 위한 방향으로 모델이 학습된다.
- 그런데 이때, 첫번째 은닉층 $H_{0}$ 로부터 $\hat{v}^{0}_{i}$를 만들어내는 것은 첫번째 은닉층 $H_{0}$ 로부터 두번째 가시층 $V_{1}$을 통해 두번째 은닉층 $H_{1}$의 사후 분포를 계산하는 것과 완벽히 동일한 과정이다. 
- 따라서 위 수식은 아래와 같이 바꿀 수 있다.
##  $\frac{\partial logp(V^{0})}{\partial w^{00}_{ij}} = <h^{0}_{j}(v^{0}_{i} - {v}^{1}_{i})>$
- 위와 같은 수식 변화에 있어 $v^{0}_{i}$가 $h^{0}_{j}$ 에 전제를 둔 확률이기 때문에 $h^{0}_{j}$에 대한 $v^{1}_{i}$의 비독립성은 문제가 되지 않는다.
- 가중치는 같은 $w_{ij}$가 여러번 중복되어 사용되기 때문에 총 미분값은 아래와 같이 모든 층 간의 가중치 미분값들의 총합으로 표현된다.
## $\frac{\partial logp(V^{0})}{\partial w^{00}_{ij}} = <h^{0}_{j}(v^{0}_{i} - {v}^{1}_{i})> + <v^{1}_{j}(h^{0}_{i} - {h}^{1}_{i})> + <h^{1}_{j}(v^{1}_{i} - {v}^{2}_{i})> + ...$
- 이 식을 풀어 쓰면, 가장 처음과 마지막 항을 제외하고 서로 상쇄되어 없어지고 이는 볼츠만 머신 수식과 같아진다.

# Restricted Boltzmann machines and contrastive divergence learning

### Figure 4 : alternating Gibbs 샘플링을 사용하는 Markov Chain
<img src="Pasted image 20240126133222.png">

### Gibbs Sampling
- MCMC Algorithm의 특별한 방법 중 하나.
- 먼저 확률변수 x를 d개의 요소로 분해할 수 있다고 가정해 보자.
	- $x = {x_{1}, x_{2}, ... , x_{d}}$
- 이때, 깁스 샘플러에서 각 요소는 1. 무작위(randomly) 또는 2. 체계적(systematically)으로 선택되며, 각 샘플은 target density f(x)의 full conditional function에서 새로운 표본으로 업데이트 된다.
- 만약 x의 현재 반복 상태가 아래와 같이 주어지면 Gibbs sampler는 다음을 반복해서 Markov Chain을 형성.
	- $x^{t} = {x^{t}_{1}, x^{t}_{2}, ... , x^{t}_{d}}$
Systematic-scan
Step 1. Draw $x^{t+1}_{1}$ from $p(x_{1} | {x^{t}_{2}, x^{t}_{3}, ... , x^{t}_{d}})$
Step 2. Draw $x^{t+1}_{2}$ from $p(x_{2} | {x^{t}_{1}, x^{t}_{3}, ... , x^{t}_{d}})$
...
Step d. Draw $x^{t+1}_{d}$ from $p(x_{1} | {x^{t}_{1}, x^{t}_{2}, ... , x^{t}_{d-1}})$
- 여기서 각각의 conditional distribution은 모두 closed form으로 Gibbs sampling에서 d개의 conditional distribution은 모두 우리가 알고 있는 standard한 분포이다.(Normal, Gamm 등)
- Gibbs의 장점
	- 3차원을 넘어가면 시각화 할 수가 없는데 깁스 샘플링을 통해 고차원의 문제를 1차원의 문제로 바꿔 해결할 수 있다.
---
- RBM에서 데이터를 생성하려면 레이어 중 하나에서 무작위 상태로 시작한 다음 교대로 Gibbs 샘플링을 수행할 수 있다. 
- Figure 4에서 처럼 한 레이어의 모든 유닛은 레이어에 있는 유닛의 현재 상태를 고려해 병렬로 업데이트 된다.
- 이는 가중치가 묶인 infinite belief net에서 데이터를 생성하는 방법과 정확히 동일함.
- RBM에서 최대 likelihood 학습을 하기 위해 두 상관 관계의 차이를 이용할 수 있다.
- $w_{ij}$에 대해 visible unit과 hidden unit의 상관관계 <$v^{0}_{i}h^{0}_{i}$>를 측정한다.
- 그런 다음 교대 Gibbs sampling을 수행해 고정 분포에 도달할 때까지 Markov Chain을 실행하고 상관관계 <$v^{0}_{i}h^{0}_{i}$>를 측정한다.
- 훈련 데이터의 로그 확률의 기울기(미분값)은 다음과 같음.(2.1에서 계산된 식 정리한 것)
##  $\frac{\partial logp(V^{0})}{\partial w_{ij}} = <v^{0}_{i}{h}^{0}_{j}> -<v^{\infty}_{i}h^{\infty}_{j}>$ 



