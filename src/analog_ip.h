#ifndef ANALOG_IP
#define ANALOG_IP

#include "util.h"

typedef struct
{
  __IO uint32_t CTRL;         // 0x00
  __IO uint32_t STAT;         // 0x04
  __IO uint32_t DATA;         // 0x08
  __IO uint32_t RESERVED[12]; // 0x0C - 0x38
  __IO uint32_t CHNL;         // 0x3C
  __IO uint32_t SEQ[16];      // 0x40 - 0x7C
} ADC_TypeDef;
#define ADC0 ((ADC_TypeDef *) 0x60000000)
//#define ADC1 ((ADC_TypeDef *) 0x60001000)
//#define ADC2 ((ADC_TypeDef *) 0x60002000)

#define ADC_CTRL_START (1 << 0) 
#define ADC_CTRL_STOP  (1 << 1) 
#define ADC_CTRL_CONT  (1 << 2) 
#define ADC_CTRL_DMAEN (1 << 3) 
#define ADC_CTRL_SCLK_DIV(__div) (__div << 16)

#define ADC_STAT_EN  (1 << 0)
#define ADC_STAT_EOC (1 << 1)

#define ADC_MAX_VALUE 0xfff

typedef enum
{
  ADC_CHANNEL0  = 1 ,
  ADC_CHANNEL1  = 2 ,
  ADC_CHANNEL2  = 3 ,
  ADC_CHANNEL3  = 4 ,
  ADC_CHANNEL4  = 5 ,
  ADC_CHANNEL5  = 6 ,
} ADC_ChannelNumTypeDef;

typedef enum
{
  ADC_SEQ_LENGTH1  = 0 ,
  ADC_SEQ_LENGTH2  = 1 ,
  ADC_SEQ_LENGTH3  = 2 ,
  ADC_SEQ_LENGTH4  = 3 ,
  ADC_SEQ_LENGTH5  = 4 ,
  ADC_SEQ_LENGTH6  = 5 ,
  ADC_SEQ_LENGTH7  = 6 ,
  ADC_SEQ_LENGTH8  = 7 ,
  ADC_SEQ_LENGTH9  = 8,
  ADC_SEQ_LENGTH10 = 9,
  ADC_SEQ_LENGTH11 = 10,
  ADC_SEQ_LENGTH12 = 11,
  ADC_SEQ_LENGTH13 = 12,
  ADC_SEQ_LENGTH14 = 13,
  ADC_SEQ_LENGTH15 = 14,
  ADC_SEQ_LENGTH16 = 15,
} ADC_SeqLengthTypeDef;

// ADC sample rate is: APB clock frequency / (1 + sclk_div) / 2 / 13
static inline void ADC_Start(ADC_TypeDef *adc, uint32_t sclk_div) { adc->CTRL = ADC_CTRL_START | ADC_CTRL_SCLK_DIV(sclk_div); }
static inline void ADC_StartContinuous(ADC_TypeDef *adc, uint32_t sclk_div) { adc->CTRL = ADC_CTRL_START | ADC_CTRL_CONT | ADC_CTRL_SCLK_DIV(sclk_div); }
static inline void ADC_StartDma(ADC_TypeDef *adc, uint32_t sclk_div) { adc->CTRL = ADC_CTRL_START | ADC_CTRL_CONT | ADC_CTRL_DMAEN | ADC_CTRL_SCLK_DIV(sclk_div); }
static inline void ADC_Stop(ADC_TypeDef *adc) { adc->CTRL |= ADC_CTRL_STOP; }
static inline void ADC_WaitForEoc(ADC_TypeDef *adc) { while (!(adc->STAT & ADC_STAT_EOC)); }
static inline void ADC_SetChannel(ADC_TypeDef *adc, ADC_ChannelNumTypeDef channel) { adc->SEQ[0] = channel; }
static inline void ADC_SetSeqLength(ADC_TypeDef *adc, ADC_SeqLengthTypeDef seq_length) { adc->CHNL = seq_length; }
static inline void ADC_SetSeqChannel(ADC_TypeDef *adc, uint32_t seq, ADC_ChannelNumTypeDef channel) { adc->SEQ[seq] = channel; }

static inline uint32_t ADC_GetStat(ADC_TypeDef *adc) { return adc->STAT; }
static inline uint32_t ADC_GetData(ADC_TypeDef *adc) { return adc->DATA; }

#define ADC0_DMA_REQ EXT_DMA0_REQ


#endif
