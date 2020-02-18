# SkUI CSS

## Introduction

This SkUI module represents a complete CSS parser and in-memory representation of a CSS rule-set.
Currently it is a work-in-progress, and far from complete.

## Implementation

CSS covers a wide array of properties and selectors.
The in-memory representation provided here makes use of variants, optionals, etc. whenever they fit the bill naturally.
The parser is written using Boost.Spirit.X3.

## Supported features

CSS is large, and once basic support is completed, some properties might still be missing or incomplete.
The below tables attempts to track what has already been implemented.

| Feature              | Implementation | Notes |
|----------------------|----------------|-------|
| Large cascade        |       :x:      |       |
| Small cascade        |       :x:      |       |
| Animations           |       :x:      |       |

### Selectors

| Feature              | Representation | Parser | Notes |
|----------------------|----------------|--------|-------|
| .class               |       :x:      |  :x:   |       |
| .class1.class2       |       :x:      |  :x:   |       |
| .class1 .class2      |       :x:      |  :x:   |       |
| #id                  |       :x:      |  :x:   |       |
| *                    |       :x:      |  :x:   |       |
| element              |       :x:      |  :x:   |       |
| element,element      |       :x:      |  :x:   |       |
| element element      |       :x:      |  :x:   |       |
| element>element      |       :x:      |  :x:   |       |
| element+element      |       :x:      |  :x:   |       |
| element~element      |       :x:      |  :x:   |       |
| [attribute]          |       :x:      |  :x:   |       |
| [attribute=value]    |       :x:      |  :x:   |       |
| [attribute~=value]   |       :x:      |  :x:   |       |
| [attribute\|=value]  |       :x:      |  :x:   |       |
| [attribute^=value]   |       :x:      |  :x:   |       |
| [attribute$=value]   |       :x:      |  :x:   |       |
| [attribute*=value]   |       :x:      |  :x:   |       |
| :active              |       :x:      |  :x:   |       |
| ::after              |       :x:      |  :x:   |       |
| ::before             |       :x:      |  :x:   |       |
| :checked             |       :x:      |  :x:   |       |
| :default             |       :x:      |  :x:   |       |
| :disabled            |       :x:      |  :x:   |       |
| :empty               |       :x:      |  :x:   |       |
| :enabled             |       :x:      |  :x:   |       |
| :first-child         |       :x:      |  :x:   |       |
| ::first-letter       |       :x:      |  :x:   |       |
| ::first-line         |       :x:      |  :x:   |       |
| ::first-of-type      |       :x:      |  :x:   |       |
| :focus               |       :x:      |  :x:   |       |
| :hover               |       :x:      |  :x:   |       |
| :in-range            |       :x:      |  :x:   |       |
| :indeterminate       |       :x:      |  :x:   |       |
| :invalid             |       :x:      |  :x:   |       |
| :lang(language)      |       :x:      |  :x:   |       |
| :last-child          |       :x:      |  :x:   |       |
| :last-of-type        |       :x:      |  :x:   |       |
| :link                |       :x:      |  :x:   |       |
| :not(selector)       |       :x:      |  :x:   |       |
| :nth-child(n)        |       :x:      |  :x:   |       |
| :nth-last-child(n)   |       :x:      |  :x:   |       |
| :nth-last-of-type(n) |       :x:      |  :x:   |       |
| :nth-of-type(n)      |       :x:      |  :x:   |       |
| :only-of-type        |       :x:      |  :x:   |       |
| :only-child          |       :x:      |  :x:   |       |
| :optional            |       :x:      |  :x:   |       |
| :out-of-range        |       :x:      |  :x:   |       |
| :placeholder         |       :x:      |  :x:   |       |
| :read-only           |       :x:      |  :x:   |       |
| :read-write          |       :x:      |  :x:   |       |
| :required            |       :x:      |  :x:   |       |
| :root                |       :x:      |  :x:   |       |
| ::selection          |       :x:      |  :x:   |       |
| :target              |       :x:      |  :x:   |       |
| :valid               |       :x:      |  :x:   |       |
| :visited             |       :x:      |  :x:   |       |

### Functions

| Feature                     | Representation     | Parser             | Notes |
|-----------------------------|--------------------|--------------------|-------|
| attr()                      |        :x:         |        :x:         |       |
| calc()                      |        :x:         |        :x:         |       |
| cubic-bezier()              | :heavy_check_mark: | :heavy_check_mark: |       |
| hsl()                       | :heavy_check_mark: | :heavy_check_mark: |       |
| hsla()                      | :heavy_check_mark: | :heavy_check_mark: |       |
| linear-gradient()           | :heavy_check_mark: | :heavy_check_mark: |       |
| radial-gradient()           | :heavy_check_mark: | :heavy_check_mark: |       |
| repeating-linear-gradient() | :heavy_check_mark: | :heavy_check_mark: |       |
| repeating-radial-gradient() | :heavy_check_mark: | :heavy_check_mark: |       |
| conical-gradient()          | :heavy_check_mark: | :heavy_check_mark: |       |
| rgb()                       | :heavy_check_mark: | :heavy_check_mark: |       |
| rgba()                      | :heavy_check_mark: | :heavy_check_mark: |       |
| var()                       |        :x:         |        :x:         |       |

### Properties

| Property                   | Representation     | Parser             | Notes |
|----------------------------|--------------------|--------------------|-------|
| align-content              | :heavy_check_mark: | :heavy_check_mark: |       |
| align-items                | :heavy_check_mark: | :heavy_check_mark: |       |
| align-self                 | :heavy_check_mark: | :heavy_check_mark: |       |
| all                        |         :x:        |        :x:         |       |
| animation                  | :heavy_check_mark: | :heavy_check_mark: |       |
| animation-delay            | :heavy_check_mark: | :heavy_check_mark: |       |
| animation-direction        | :heavy_check_mark: | :heavy_check_mark: |       |
| animation-duration         | :heavy_check_mark: | :heavy_check_mark: |       |
| animation-fill-mode        | :heavy_check_mark: | :heavy_check_mark: |       |
| animation-iteration-count  | :heavy_check_mark: | :heavy_check_mark: |       |
| animation-name             | :heavy_check_mark: | :heavy_check_mark: |       |
| animation-play-state       | :heavy_check_mark: | :heavy_check_mark: |       |
| animation-timing-Function  | :heavy_check_mark: | :heavy_check_mark: |       |
| backface-visibility        | :heavy_check_mark: | :heavy_check_mark: |       |
| background                 |         :x:        |        :x:         |       |
| background-attachment      | :heavy_check_mark: | :heavy_check_mark: |       |
| background-blend-mode      | :heavy_check_mark: | :heavy_check_mark: |       |
| background-clip            | :heavy_check_mark: | :heavy_check_mark: |       |
| background-color           | :heavy_check_mark: | :heavy_check_mark: |       |
| background-image           | :heavy_check_mark: | :heavy_check_mark: |       |
| background-origin          | :heavy_check_mark: | :heavy_check_mark: |       |
| background-position        | :heavy_check_mark: | :heavy_check_mark: |       |
| background-repeat          | :heavy_check_mark: | :heavy_check_mark: |       |
| background-size            | :heavy_check_mark: | :heavy_check_mark: |       |
| border                     |         :x:        |        :x:         |       |
| border-bottom              |         :x:        |        :x:         |       |
| border-bottom-color        |         :x:        |        :x:         |       |
| border-bottom-left-radius  |         :x:        |        :x:         |       |
| border-bottom-right-radius |         :x:        |        :x:         |       |
| border-bottom-style        |         :x:        |        :x:         |       |
| border-bottom-width        |         :x:        |        :x:         |       |
| border-collapse            |         :x:        |        :x:         |       |
| border-color               |         :x:        |        :x:         |       |
| border-image               |         :x:        |        :x:         |       |
| border-image-outset        |         :x:        |        :x:         |       |
| border-image-repeat        |         :x:        |        :x:         |       |
| border-image-slice         |         :x:        |        :x:         |       |
| border-image-source        |         :x:        |        :x:         |       |
| border-image-width         |         :x:        |        :x:         |       |
| border-left                |         :x:        |        :x:         |       |
| border-left-color          |         :x:        |        :x:         |       |
| border-left-style          |         :x:        |        :x:         |       |
| border-left-width          |         :x:        |        :x:         |       |
| border-radius              |         :x:        |        :x:         |       |
| border-right               |         :x:        |        :x:         |       |
| border-right-color         |         :x:        |        :x:         |       |
| border-right-style         |         :x:        |        :x:         |       |
| border-right-width         |         :x:        |        :x:         |       |
| border-spacing             |         :x:        |        :x:         |       |
| border-style               |         :x:        |        :x:         |       |
| border-top                 |         :x:        |        :x:         |       |
| border-top-color           |         :x:        |        :x:         |       |
| border-top-left-radius     |         :x:        |        :x:         |       |
| border-top-right-radius    |         :x:        |        :x:         |       |
| border-top-style           |         :x:        |        :x:         |       |
| border-top-width           |         :x:        |        :x:         |       |
| border-width               |         :x:        |        :x:         |       |
| bottom                     |         :x:        |        :x:         |       |
| box-decoration-break       | :heavy_check_mark: | :heavy_check_mark: |       |
| box-shadow                 | :heavy_check_mark: | :heavy_check_mark: |       |
| box-sizing                 | :heavy_check_mark: | :heavy_check_mark: |       |
| caption-side               | :heavy_check_mark: | :heavy_check_mark: |       |
| caret-color                |         :x:        |        :x:         |       |
| charset                    |         :x:        |        :x:         |       |
| clear                      |         :x:        |        :x:         |       |
| clip                       |         :x:        |        :x:         |       |
| color                      |         :x:        |        :x:         |       |
| column-count               |         :x:        |        :x:         |       |
| column-fill                |         :x:        |        :x:         |       |
| column-gap                 |         :x:        |        :x:         |       |
| column-rule                |         :x:        |        :x:         |       |
| column-rule-color          |         :x:        |        :x:         |       |
| column-rule-style          |         :x:        |        :x:         |       |
| column-rule-width          |         :x:        |        :x:         |       |
| column-span                |         :x:        |        :x:         |       |
| column-width               |         :x:        |        :x:         |       |
| columns                    |         :x:        |        :x:         |       |
| content                    |         :x:        |        :x:         |       |
| counter-increment          |         :x:        |        :x:         |       |
| counter-reset              |         :x:        |        :x:         |       |
| cursor                     |         :x:        |        :x:         |       |
| direcion                   |         :x:        |        :x:         |       |
| display                    |         :x:        |        :x:         |       |
| empty-cells                |         :x:        |        :x:         |       |
| filter                     |         :x:        |        :x:         |       |
| flex                       |         :x:        |        :x:         |       |
| flex-basis                 |         :x:        |        :x:         |       |
| flex-direction             |         :x:        |        :x:         |       |
| flex-flow                  |         :x:        |        :x:         |       |
| flex-grow                  |         :x:        |        :x:         |       |
| flex-shrink                |         :x:        |        :x:         |       |
| flex-wrap                  |         :x:        |        :x:         |       |
| float                      |         :x:        |        :x:         |       |
| font                       |         :x:        |        :x:         |       |
| font-face                  |         :x:        |        :x:         |       |
| font-family                |         :x:        |        :x:         |       |
| font-kerning               |         :x:        |        :x:         |       |
| font-size                  |         :x:        |        :x:         |       |
| font-size-adjust           |         :x:        |        :x:         |       |
| font-stretch               |         :x:        |        :x:         |       |
| font-style                 |         :x:        |        :x:         |       |
| font-variant               |         :x:        |        :x:         |       |
| font-weight                |         :x:        |        :x:         |       |
| grid                       |         :x:        |        :x:         |       |
| grid-area                  |         :x:        |        :x:         |       |
| grid-auto-columns          |         :x:        |        :x:         |       |
| grid-auto-flows            |         :x:        |        :x:         |       |
| grid-auto-rows             |         :x:        |        :x:         |       |
| grid-column                |         :x:        |        :x:         |       |
| grid-column                |         :x:        |        :x:         |       |
| grid-column-end            |         :x:        |        :x:         |       |
| grid-column-gap            |         :x:        |        :x:         |       |
| grid-column-start          |         :x:        |        :x:         |       |
| grid-gap                   |         :x:        |        :x:         |       |
| grid-row                   |         :x:        |        :x:         |       |
| grid-row-end               |         :x:        |        :x:         |       |
| grid-row-gap               |         :x:        |        :x:         |       |
| grid-row-start             |         :x:        |        :x:         |       |
| grid-template              |         :x:        |        :x:         |       |
| grid-template-areas        |         :x:        |        :x:         |       |
| grid-template-columns      |         :x:        |        :x:         |       |
| grid-template-rows         |         :x:        |        :x:         |       |
| hanging-punctuation        |         :x:        |        :x:         |       |
| height                     |         :x:        |        :x:         |       |
| hyphens                    |         :x:        |        :x:         |       |
| import                     |         :x:        |        :x:         |       |
| isolation                  |         :x:        |        :x:         |       |
| justify-content            |         :x:        |        :x:         |       |
| keyframes                  |         :x:        |        :x:         |       |
| left                       |         :x:        |        :x:         |       |
| letter-spacing             |         :x:        |        :x:         |       |
| line-height                |         :x:        |        :x:         |       |
| list-style                 |         :x:        |        :x:         |       |
| list-style-image           |         :x:        |        :x:         |       |
| list-style-position        |         :x:        |        :x:         |       |
| list-style-stype           |         :x:        |        :x:         |       |
| margin                     |         :x:        |        :x:         |       |
| margin-bottom              |         :x:        |        :x:         |       |
| margin-left                |         :x:        |        :x:         |       |
| margin-right               |         :x:        |        :x:         |       |
| margin-top                 |         :x:        |        :x:         |       |
| max-height                 |         :x:        |        :x:         |       |
| max-width                  |         :x:        |        :x:         |       |
| media                      |         :x:        |        :x:         |       |
| min-height                 |         :x:        |        :x:         |       |
| min-width                  |         :x:        |        :x:         |       |
| mix-blend-mode             |         :x:        |        :x:         |       |
| object-fit                 |         :x:        |        :x:         |       |
| object-position            |         :x:        |        :x:         |       |
| opacity                    |         :x:        |        :x:         |       |
| order                      |         :x:        |        :x:         |       |
| outline                    |         :x:        |        :x:         |       |
| outline-color              |         :x:        |        :x:         |       |
| outline-offset             |         :x:        |        :x:         |       |
| outline-style              |         :x:        |        :x:         |       |
| outline-width              |         :x:        |        :x:         |       |
| overflow                   |         :x:        |        :x:         |       |
| overflow-x                 |         :x:        |        :x:         |       |
| overflow-y                 |         :x:        |        :x:         |       |
| padding                    |         :x:        |        :x:         |       |
| padding-bottom             |         :x:        |        :x:         |       |
| padding-left               |         :x:        |        :x:         |       |
| padding-right              |         :x:        |        :x:         |       |
| padding-top                |         :x:        |        :x:         |       |
| page-break-after           |         :x:        |        :x:         |       |
| page-break-before          |         :x:        |        :x:         |       |
| page-break-inside          |         :x:        |        :x:         |       |
| perspective                |         :x:        |        :x:         |       |
| perspective-origin         |         :x:        |        :x:         |       |
| pointer-events             |         :x:        |        :x:         |       |
| position                   |         :x:        |        :x:         |       |
| quotes                     |         :x:        |        :x:         |       |
| resize                     |         :x:        |        :x:         |       |
| right                      |         :x:        |        :x:         |       |
| scroll-behavior            |         :x:        |        :x:         |       |
| tab-size                   |         :x:        |        :x:         |       |
| table-layout               |         :x:        |        :x:         |       |
| text-align                 |         :x:        |        :x:         |       |
| text-align-last            |         :x:        |        :x:         |       |
| text-decoration            |         :x:        |        :x:         |       |
| text-decoration-color      |         :x:        |        :x:         |       |
| text-decoration-line       |         :x:        |        :x:         |       |
| text-decoration-style      |         :x:        |        :x:         |       |
| text-indent                |         :x:        |        :x:         |       |
| text-justify               |         :x:        |        :x:         |       |
| text-overflow              |         :x:        |        :x:         |       |
| text-shadow                |         :x:        |        :x:         |       |
| text-transform             |         :x:        |        :x:         |       |
| top                        |         :x:        |        :x:         |       |
| transform                  |         :x:        |        :x:         |       |
| transform-origin           |         :x:        |        :x:         |       |
| transform-style            |         :x:        |        :x:         |       |
| transition                 |         :x:        |        :x:         |       |
| transition-delay           |         :x:        |        :x:         |       |
| transition-duration        |         :x:        |        :x:         |       |
| transition-property        |         :x:        |        :x:         |       |
| transition-timing-function |         :x:        |        :x:         |       |
| unicode-bidi               |         :x:        |        :x:         |       |
| user-selection             |         :x:        |        :x:         |       |
| vertical-align             |         :x:        |        :x:         |       |
| visibility                 |         :x:        |        :x:         |       |
| white-space                |         :x:        |        :x:         |       |
| width                      |         :x:        |        :x:         |       |
| word-break                 |         :x:        |        :x:         |       |
| word-spacing               |         :x:        |        :x:         |       |
| word-wrap                  |         :x:        |        :x:         |       |
| z-index                    |         :x:        |        :x:         |       |
