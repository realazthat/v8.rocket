
## Status
I am currently trying to get jQuery selectors running. Loading jQuery finally does not give errors, however only by-id and perhaps by-tag selectors are working right now. Also events like click() seem to be working.

So for now, I am sort of using jQuery as a benchmark of the DOM implementation.

Note that input elements etc. are not specialized above HTMLElement, so setting their value property is useless for now (Wrap controls TODO).



## TODO

- Wrap controls
- Implement removeEventListener
- Implement/Use EventListenerInstancer?
- Finish DOM (of course)
- Test suites?
- Example
- Example html/javascript
- DocumentFragment
- Supply missing functionality that jQuery needs to function
- setTimeout()
- Fix line number's in ReportException()

## Improvements required (or preferred) in libRocket

- High: FormControls should respect readonly attribute
- Med: A way for a Form to find its child form controls
- Low: A way for a FormControl to find its form
- Low: defaultValue for FormControls
- Med: Should rocket respect GetRML(), SetRML() for FormControls?

## WORKAROUNDS
- I don't think it is possible to get access to the HEAD tag etc. in libRocket
- In libRocket, ElementDocument is the BODY tag; in DOM, HTMLDocument is usually an HTML tag (equivelent to #root, which here is a generic element)
- In libRocket, GetOwnerDocument() returns the BODY tag, in DOM, ownerDocument points to the HTMLDocument
