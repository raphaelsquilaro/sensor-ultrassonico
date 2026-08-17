# README — Sensor Ultrassônico

**Autor:** Raphael Campos Squilaro
**Projeto:** Using an Ultrasonic Sensor

## 📌 Sobre o projeto

Este projeto utiliza um **sensor ultrassônico** para medir a distância entre o sensor e um objeto.

O programa envia um pulso ultrassônico pelo pino `TRIG`, recebe o sinal de retorno pelo pino `ECHO` e calcula a distância com base no tempo que o sinal levou para retornar.

O resultado é exibido no **Monitor Serial**, em centímetros.

## 🔧 Componentes utilizados

* Microcontrolador compatível com Arduino/ESP32
* Sensor ultrassônico
* Fios de conexão
* Cabo USB para programação e alimentação

## 📍 Configuração dos pinos

```cpp
#define PINO_TRIG 34
#define PINO_ECHO 21
```

Aqui são definidos os pinos utilizados pelo sensor:

* `PINO_TRIG` → pino responsável por **enviar** o pulso ultrassônico.
* `PINO_ECHO` → pino responsável por **receber** o retorno do pulso.

> **Observação:** em algumas placas, determinados GPIOs possuem restrições para entrada ou saída. Portanto, é importante verificar o modelo da placa antes de realizar a ligação.

---

## ⚙️ Passo a passo do código

### 1. Inicialização da comunicação serial

```cpp
Serial.begin(9600);
```

Essa instrução inicia a comunicação entre a placa e o computador utilizando uma velocidade de **9600 bits por segundo**.

Ela permite visualizar a distância calculada no **Monitor Serial**.

---

### 2. Configuração dos pinos

```cpp
pinMode(PINO_TRIG, OUTPUT);
pinMode(PINO_ECHO, INPUT);
```

Os pinos são configurados de acordo com suas funções:

* `TRIG` como `OUTPUT`, pois a placa precisa enviar um sinal.
* `ECHO` como `INPUT`, pois a placa precisa receber o sinal de retorno.

---

### 3. Preparação do sensor

Dentro do `loop()`, o código começa colocando o `TRIG` em nível baixo:

```cpp
digitalWrite(PINO_TRIG, LOW);
delay(20);
```

Isso garante que o pino esteja inicialmente desligado antes de enviar um novo pulso.

---

### 4. Envio do pulso ultrassônico

Depois disso:

```cpp
digitalWrite(PINO_TRIG, HIGH);
delay(20);
digitalWrite(PINO_TRIG, LOW);
```

O pino `TRIG` é colocado em nível alto e, após um pequeno intervalo, volta para nível baixo.

Esse sinal faz com que o sensor ultrassônico envie uma onda sonora de alta frequência.

---

### 5. Medição do tempo de retorno

```cpp
duracao = pulseIn(PINO_ECHO, HIGH);
```

A função `pulseIn()` mede quanto tempo o pino `ECHO` permaneceu em nível alto.

Esse tempo representa o período necessário para o sinal ultrassônico:

1. sair do sensor;
2. atingir o objeto;
3. retornar ao sensor.

O valor é armazenado na variável:

```cpp
long duracao;
```

---

### 6. Cálculo da distância

```cpp
distancia = (duracao / 2) * 0.0343;
```

Aqui o programa transforma o tempo medido em distância.

A divisão por `2` é necessária porque o tempo medido corresponde ao **percurso de ida e volta** do sinal.

O valor `0.0343` representa aproximadamente a velocidade do som no ar em **centímetros por microssegundo**.

A fórmula utilizada é, portanto:

```text
distância = (tempo × velocidade do som) / 2
```

---

### 7. Exibição do resultado

```cpp
Serial.print("A distância é de: ");
Serial.print(distancia);
Serial.println(" cm");
```

O resultado é enviado para o Monitor Serial.

Por exemplo:

```text
A distância é de: 25 cm
```

---

### 8. Intervalo entre as medições

```cpp
delay(2000);
```

Após mostrar o resultado, o programa espera **2 segundos** antes de realizar uma nova medição.

Assim, o sensor não realiza medições continuamente em alta velocidade.

---

## 🔄 Fluxo de funcionamento

O funcionamento do programa pode ser resumido da seguinte maneira:

```text
Início
  ↓
Configura comunicação Serial
  ↓
Configura TRIG como saída
  ↓
Configura ECHO como entrada
  ↓
Envia pulso ultrassônico
  ↓
Aguarda o retorno do sinal
  ↓
Mede o tempo de retorno
  ↓
Calcula a distância
  ↓
Exibe a distância no Monitor Serial
  ↓
Espera 2 segundos
  ↓
Repete o processo
```

## 🧮 Exemplo do cálculo

Supondo que o sensor tenha medido um tempo de aproximadamente `1458 µs`:

```text
distância = (1458 / 2) × 0,0343
distância ≈ 25 cm
```

Portanto, o programa exibiria aproximadamente:

```text
A distância é de: 25 cm
```

## ▶️ Como executar

1. Monte o circuito conectando o sensor aos pinos definidos no código.
2. Abra o código na IDE compatível com sua placa.
3. Conecte a placa ao computador.
4. Compile o programa.
5. Faça o upload para a placa.
6. Abra o **Monitor Serial**.
7. Configure a velocidade para **9600 baud**.
8. Aproxime ou afaste um objeto do sensor e observe as medições.

## 💻 Código completo

```cpp
//Author: Raphael Campos Squilaro
//Project: Using an ultrasonic sensor

#define PINO_TRIG 34
#define PINO_ECHO 21

void setup() {
  Serial.begin(9600);
  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
}

void loop() {
  long duracao, distancia;

  digitalWrite(PINO_TRIG, LOW);
  delay(20);
  digitalWrite(PINO_TRIG, HIGH);
  delay(20);
  digitalWrite(PINO_TRIG, LOW);

  duracao = pulseIn(PINO_ECHO, HIGH);
  distancia = (duracao / 2) * 0.0343;

  Serial.print("A distância é de: ");
  Serial.print(distancia);
  Serial.println(" cm");

  delay(2000);
}
```

## 🎯 Objetivo do projeto

O objetivo é demonstrar, de forma prática, como utilizar um **sensor ultrassônico para medir distâncias**, trabalhando com:

* Entrada e saída digital;
* Comunicação Serial;
* Medição de duração de pulsos;
* Conversão de tempo em distância;
* Estrutura `setup()` e `loop()` do Arduino.
