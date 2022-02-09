;;;; entity
;; the underlying datatype for structures and creatures

#lang racket/base

(require racket/function
         racket/class racket/class/iop
         racket/contract)

(require "pos.rkt")

(provide entity<%> entity%)

(define entity<%>
  (interface ()
             is-drawable?
             move-to move))

(define/contract entity%

  any/c
  
  (class* object% (entity<%>)
    (super-new)

    (init-field
      [pos (new pos%)]
      [content "o"]
      [visable #t])

    (define/public is-drawable?
      (λ ()
        (and
          visable
          (send pos is-valid?))))

    (define/public move-to
      (λ (y x)
        (send pos set-yx y x)))    

    (define/public move
      (λ (dy dx)
        (void)))))
;        (move-to (+ (send y dy) (+ x dx)))))))
