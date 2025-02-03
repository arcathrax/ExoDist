# parent- and childcomponents

Eine UI besteht meistens aus vielen verschiedenen Elementen.
Diese sind oftmals unterteilt in *parent-* oder *childcomponents*.
Man kann z.B. ein Container erstellen,
welcher einen Button und ein Label beinhaltet.

In Juce haben *components* oftmals eine `paint` funktion,
um sich selber zu zeichnen.
Andere *components* beinhalten andere *components* und
zeichnen nur ganz wenig dazu.

