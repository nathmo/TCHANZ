# Documentation final de TCHANZ
## Approche pour les déplacements
### Lieu de naissance des fourmis :
le lieux de naissance des fourmis est choisis au hazard pour garantir une part de fourmis sur chaque famille de case et donc maximiser le nombre de nourriture qui peuvent être atteintes dans le cas des collector ainsi que d'assurer certaines répartion a peut pret égal des autres fourmis dans la fourmilliere.

### Generator :
la fourmis générator essaie de se placer au centre de la fourmillière sauf si une bordure de 3 carré ne peut être garantie entre la générator et le bord de la fourmillière où les fourmis peuvent apparaitre. Ceci dans le but de permettre la génération de fourmis meme avec la plus petite fourmilliere possible en lui laissant l'opportunité de grandir dans le pire des cas.

### Collector :
Dans le cas ou deux chemin sont égaux, la collector calcule le nombre de superposition a chaque pas et choisis le chemin qui cummule le moins de superposition avec d'autre entité
une fourmis collector sans nourriture cible se contente de se déplacer au hazard sur le plateau dans le but de maximiser ses chances qu'une des collector sois au plus proche d'une nourriture quand celle-ci apparaitra

### Defensor :
Defensors calcul la bordure la plus proche et s'y rend. une fois sur la bordure elle se contente de se déplacer d'un coté et de l'autre pour ne pas bloquer une collector ou predator qui sortirais de la fourmillière.

### Predator :
la fourmis prédator tente simplement de retourner dans sa fourmilliere et s'y ballade au hazard. Les déplacement au hazard étant là pour éviter les blocage avec d'autre fourmis de la fourmilliere.

## Screenshot

## Méthodologie
Nous avons mis en place un git depuis le début. nous étions ainsi capable de programmer ensemble (en général le vendredi en séance d'exo) et seul quand nous avions du temps libre. Nous travaillons généralement ensemble pour résoudre les bugs les plus corriace et seul le reste du temps avec des meetings régulier pour tenir l'autre a jour quand sur l'avancement global, les prochaines étapes et le fonctionnenemnt du code déjà écris. Nous nous somme répartis les fonctions et modules en fonction des affinité. L'un de nous ayant plus d'affinité avec la structure du code et l'autre avec l'implémentation d'algorithme.
[Nathann] s'est chargé du module simulation ainsi que des machines d'état de chaque fourmis et de la génération et la mort des entity en faisant appelles aux fonction que [Felipe] se chargait de faire pendant ce temps là. [Felipe] à fait les algoritme pour permettre aux fourmis de trouver les nourriture, leurs maison, les autres fourmis a attaquer ou encore la bordure la plus proche ainsi que le pathfinding ou encore le calcul de distance. Nous avons finalisé le path finding ensemble suite a quelque complications algoritmique.

Nous avions mis en place une série de test automatique que git lançait a chaque push pour s'assurer que les modifications ne cassait pas le travail antérieur pour le rendu 1.
les test d'intégration automatique de la simulations étant plus compliqué a mettre en place avec une interface graphique, nous nous somme contenté de faire des test unitaire manuelle sur les fonctions au fur et a mesure et de souvent tester l'execution du programme dans son ensemble.

Les bugs les plus courant était l'oubli de vérifier si un pointeur contenait autre chose que nullptr ce qui résultait en segfault. Mais les plus compliquées a débugger étaient les faute d'algoritmique qui se cachait généralement de manière cryptique.

## Conclusion

Le projet est intéressant dans son ensemble. Le fait que certain détails d'implémentation soit imposé n'était pas toujours agréable mais la documentation et le discourse évitaient que cela crée trop de problème. Nous nous sommes bien ammusé même si le projet est relativement chronophage. Il nous semble que nous avons fait du bon travail dans l'ensemble et utilisé judicieusement les outils de dévellopement tel que git, WSL (qui supporte le GUI sur windows 11) et les pipeline de test. Il est dommage que le projet utilise GTKmm et pas quelque chose comme QT qui est un peu plus moderne mais cela fut intéressant dans l'ensemble.
