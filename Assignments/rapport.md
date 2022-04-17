# TASK 0

## A- Exécution

Pour ajouter un avion, il faut cliquer sur la touche "c".
Pour quitter le programme, on doit appuyer sur la touche "x" ou "q".
La touche 'f' sert à mettre la fenêtre en grand écran.

Que est le comportement de l'avion ?
étape 1: L'avion atterit, se gare, repart à la piste et redécolle puis passe à l'étape 2. 
étape 2: il revient ensuite faire un tour de l'aéroport et réeffectue l'étape 1
Chaque avion fait ces 2 étapes en boucle en commençant par la 1.

La console affiche quand un avion est en train d'atterrir avec ".... is now landing" et quand il décolle ".... lift off". Elle affiche également "now servicing ...." quand il se gare et "done servicing ...." quand il part et retourne à la piste.

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?
étape 1: L'avion atterit, se gare, repart à la piste et redécolle puis passe à l'étape 2. 
étape 2: il revient ensuite faire un tour de l'aéroport et effectue l'étape 3 s'il n'y a pas de place pour se garer, sinon l'étape 1
étape 3: fait le tour de l'aéroport en attendant qu'une place se libère pour se garer et effectuer l'étape 1
Les 3 premiers avions commencent par l'étape 1.
Le 4ème avion commence par l'étape 3 car il n'a plus de places pour se garer (occupées par les 3 premiers avions).

## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.

`AircraftType`: représente toutes les caractéristiques d'un avion
`Aircraft`: représente un avion
`AirportType`: représente toutes les caractéristiques de l'aéroport
`Airport`: représente un aéroport
`Point2D`: représente un point avec 2 coordonées x et y
`Point3D`: représente un point avec 3 corrdonées x,y et z
`Runway`: représente les inforlmations d'une piste
`Terminal`: représente les informations d'un terminal
`TowerSimulation`: représente l'animation vue en fenêtre
`Tower`: représente la tour de contrôle
`Waypoint`: représente le point où se trouve l'avion dans l'espace
`WaypointType`: représente un enum qui dit si l'avion est au sol, dans le terminal ou sur le sol

Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.

`Tower`: 
- `WaypointQueue get_instructions(Aircraft& aircraft)` : cette fonction sert à donner les instructions aux avions par rapport à leur position, si l'avion est pas dans un terminal, si ca distance par rapport a l'aéroport est inférieure à 5, si il y a de la place disponible dans le terminal, alors il dit a l'avion d'y aller, sinon l'avion continue de faire des cercles autour de l'aéroport. Si l'avion est dans un terminal, alors la tour de controle renvoie un nouveau `path`, chemin pour l'avion
- `void arrived_at_terminal(const Aircraft& aircraft)` : cette fonction va permettre de démarrer le service d'un terminal lorsqu'un avion y rentre.

`Aircraft`:
- `const std::string& get_flight_num() const `: retourne le numéro de l'avion
- `float distance_to(const Point3D& p) const `: retourne la distance entre l'avion et le point p
- `void display() const override `: affiche l'avion sur la fenêtre
- `void move() override `: dirige l'avion en fonction de sa position dans la map, de s'il est dans les airs, ou dans un terminal, etc...

`Airport`:
- `Tower& get_tower()` : retourne la tour de contrôle de l'aéroport
- `void display() const override` : affiche l'aéroport dans la fenêtre 
- `void move() override `: va appeler la fonction move sur chaque terminal que l'aéroport possède

`Terminal`:
- `bool in_use() const `: retour true si le terminal contient un avion, faux sinon
- `bool is_servicing() const `: retourne true si il est en service, faux sinon
- `void assign_craft(const Aircraft& aircraft)` : assigne un avion au terminal
- `void start_service(const Aircraft& aircraft)` : commence le service du terminal
- `void finish_service()` : met un terme au service du terminal
- `void move() override `: si le terminal contient un avion et est en service, alors on incrémente la valeur de `service_progress` qui sert de timer au service du terminal

`Tower` utilise la classe `Airport` en en prenant un dans son constructeur, `Tower` utilise également Aircraft pour ses deux fonctions publiques get_instructions et arrived_at_terminal.
`Aicraft` utilise la classe `Tower` en l'assignant avec son constructeur.
`Airport` possède un champs `Tower`, qui sera retourné dans la fonction `get_tower`, utilise la classe `Terminal` en l'utilisant pour créer un champs qui sera une liste de `Terminal` et pour retourner un `Terminal` avec `get_terminal`. Enfin `Airport` utilise la classe `Aicraft` dans la fonction `reserve_terminal`.
`Terminal` possède un champs qui utilise la classe `Aicraft`, et ce champs est utilisé par plusieurs fonctions-membres.

Les classes et fonctions qui sont impliquées dans la génération du chemin d'un avion sont la classe `Tower` avec `get_instructions` et la classe `Aicraft` avec la fonction move.
Le conteneur de la librairie standard qui a été choisi pour représenter le chemin est `std::deque<Waypoint>` car on peut accéder au début et à la fin du conteneur en ajoutant ou retirant du deque.

## C- Bidouillons !

Les vitesses maximales et accélérations de chaque avion sont définies dans la classe `AircraftType` avec `max_air_speed` et `max_accel`. 
C'est dans la fonction `init_aircraft_types` qu'on attribue la vitesse et l'accéléation aux différents types d'avions, c'est donc sur la ligne `aircraft_types[2] = new AircraftType { .02f, .05f, .02f, MediaPath { "concorde_af.png" } };` que j'ai changé les vitesses et accélérations en `aircraft_types[2] = new AircraftType { .02f, .10f, .04f, MediaPath { "concorde_af.png" } };`.

La variable `ticks_per_sec` dans le fichier `opengl_interface.hpp` est celle qui contrôle le framerate de la simulation.
J'ai ajouté 2 lignes dans la fonction `create_keystrokes` qui augmente ou diminiue le framerate si on appuie sur k ou l. 
Si je mets le framerate à 0, le programme s'arrête.
Pour mettre le programme en pause, je crée une nouvelle variable boolean `pause` dans `opengl_interface.hpp` que je vais utiliser dans le la fonction `timer()` de `opengl_interface.cpp `pour arrêter les mouvements des items du programme si pause est True. On change la valeur de pause avec la touche p.

C'est la variable `SERVICE_CYCLES` qui contrôle le temps de débarquement des avions.

Pour q'un avion soit supprimé de la `move_queue`, il suffit de rajouter un champs booléen `has_landed` dans la classe `Aicraft` qui nous dira si l'avion a déjà atterri. Si c'est le cas, alors la fonction `timer` regardera le rendu de la fonction `move()` de `Aircraft`(qui est bool et plus void), si c'est true, alors on laisse l'avion dans la `move_queue`, on le retire sinon. La fonction `move` de `Aircraft` va renvoyer faux si l'avion n'a plus de chemin (sa liste de Waypoint est vide) et que il a déjà atterri. Le champs `has_landed` est modifé dans la fonction `get_instructions()` de `Tower`, lorsque l'avion redécolle.

Pour que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit, il suffit d'autorise le constructeur et le destructeur de `Displayable` à ajouter ou effacer des éléments de la `display_queue`.

Pour que la tour de contrôle puisse stocker un `Aircraft` et le terminal qui lui est associé, on peut à présent utiliser une map qui aura comme clé un `Aicraft` et comme valeur l'indice du terminal associé.

## D- Théorie

La classe `Tower` peut réserver un terminal de l'aéroport en créant une map `reserved_terminals` qui prendra un `Aicraft` et un `size_t` qui est le numéro du terminal.

Dans la fonction `void Aircraft::turn(Point3D direction)`, nous ne sommes pas passés par une réference constante car la direction est amenée à être modifiée donc on ne veut pas que cela impacte la direction passée en paramètre.

Il n'est pas possible d'éviter la copie du `Point3D` passé en paramètre car la direction n'est pas passée en référence, donc il faut que la fonction copie la direction si elle veut la modifier, si modification il y a.


# TASK 1

## Objectif 1 - Référencement des avions

### A - Choisir l'architecture

Chaque option a un pour et un contre, pour la première option, créer une nouvelle classe permet de d'effectuer de la délégation et d'appliquer les bases de la programmation orientée objet, le seul point négatif est qu'il va falloir créer une nouvelle classe à chaque fois que l'on voudra ajouter un avion. Le point positif de la deuxième option est qu'on pourra appeler plus facilement cette méthode dans le programme mais le principe orienté objet n'est pas forcément respecté.

### B - Déterminer le propriétaire de chaque avion

C'est la fonction `move()` de la classe `Aircraft` qui retire les avions de la `move_queue` et la fonction `timer()` de `opengl_interface.cpp` qui est responsable de détruire les avions en les retirant de la `display_queue`.

Ce sont `move_queue` et `display_queue` qui contiennent une référence sur un avion au moment où il doit être détruit.

Pour supprimer la référence sur un avion qui va être détruit dans ces deux structures, comme on parcout la liste `move_queue` avec un itérateur dans `timer()` on ne peut pas utiliser le destructeur de `DynamicObject`, il faut utiliser la fonction erase du unordered_set. En revanche pour supprimer un `Displayable` de `display_queue`, on utilise le destructeur de la classe `Displayable`.

## Objectif 2 - Usine à avions

### A - Création d'une factory

Il définir `context_initializer` dans `TowerSimulation` avant de définir `aircraft_factory` pour s'assurer que le constructeur de `context_initializer` est appelé avant celui de `factory`.

# TASK 4

### Objectif 1 - Devant ou derrière ? 

Pour que le programme compile, il faut que l'appel à la fonction `add_waypoint` se fasse avec un template dans lequel le flag sera assigné à false d'office.

Dans la fonction `test_generic_points`, quand j'essaye d'instancier un `Point2D` avec 3 arguments, alors le programme ne compile pas, cette erreur ne se produit que maintenant car nous avons fait de `Point2D` et `Point3D` des alias sur des classes générées à partir du template `Point` avec respectivement 2 floats et 3 floats.

Maintenant, si j'essaye d'instancier un `Point3D` avec 2 arguments, le programme compile.






