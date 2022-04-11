# Se familiariser avec l'existant

## A- Exécution

Compilez et lancez le programme.

Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.
Sur quelle touche faut-il appuyer pour ajouter un avion ?
# Pour ajouter un avion, il faut cliquer sur la touche "c".

Comment faire pour quitter le programme ?
# Pour quitter le programme, on doit appuyer sur la touche "x" ou "q".

A quoi sert la touche 'F' ?
# La touche 'f' sert à mettre la fenêtre en grand écran.

Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?
# étape 1: L'avion atterit, se gare, repart à la piste et redécolle puis passe à l'étape 2. 
# étape 2: il revient ensuite faire un tour de l'aéroport et réeffectue l'étape 1
# Chaque avion fait ces 2 étapes en boucle en commençant par la 1.

Quelles informations s'affichent dans la console ?
# La console affiche quand un avion est en train d'atterrir avec ".... is now landing" et quand il décolle ".... lift off". Elle affiche également "now servicing ...." quand il se gare et "done servicing ...." quand il part et retourne à la piste.

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?
# étape 1: L'avion atterit, se gare, repart à la piste et redécolle puis passe à l'étape 2. 
# étape 2: il revient ensuite faire un tour de l'aéroport et effectue l'étape 3 s'il n'y a pas de place pour se garer, sinon l'étape 1
# étape 3: fait le tour de l'aéroport en attendant qu'une place se libère pour se garer et effectuer l'étape 1
# Les 3 premiers avions commencent par l'étape 1.
# Le 4ème avion commence par l'étape 3 car il n'a plus de places pour se garer (occupées par les 3 premiers avions).

## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.

# AircraftType: représente toutes les caractéristiques d'un avion
# Aircraft: représente un avion
# AirportType: représente toutes les caractéristiques de l'aéroport
# Airport: représente un aéroport
# Point2D: représente un point avec 2 coordonées x et y
# Point3D: représente un point avec 3 corrdonées x,y et z
# Runway: représente les inforlmations d'une piste
# Terminal: représente les informations d'un terminal
# TowerSimulation: représente l'animation vue en fenêtre
# Tower: représente la tour de contrôle
# Waypoint: représente le point où se trouve l'avion dans l'espace
# WaypointType: représente un enum qui dit si l'avion est au sol, dans le terminal ou sur le sol

Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.

# Tower: 
# - WaypointQueue get_instructions(Aircraft& aircraft) : cette fonction sert à donner les instructions aux avions par rapport à leur position, si l'avion est pas dans un terminal, si ca distance par rapport a l'aéroport est inférieure à 5, si il y a de la place disponible dans le terminal, alors il dit a l'avion d'y aller, sinon l'avion continue de faire des cercles autour de l'aéroport. Si l'avion est dans un terminal, alors la tour de controle renvoie un nouveau "path", chemin pour l'avion
# - void arrived_at_terminal(const Aircraft& aircraft) : cette fonction va permettre de démarrer le service d'un terminal lorsqu'un avion y rentre.

# Aircraft:
# - const std::string& get_flight_num() const : retourne le numéro de l'avion
# - float distance_to(const Point3D& p) const : retourne la distance entre l'avion et le point p
# - void display() const override : affiche l'avion sur la fenêtre
# - void move() override : dirige l'avion en fonction de sa position dans la map, de s'il est dans les airs, ou dans un terminal, etc...

# Airport:
# - Tower& get_tower() : retourne la tour de contrôle de l'aéroport
# - void display() const override : affiche l'aéroport dans la fenêtre 
# - void move() override : va appeler la fonction move sur chaque terminal que l'aéroport possède

# Terminal:
# - bool in_use() const : retour true si le terminal contient un avion, faux sinon
# - bool is_servicing() const : retourne true si il est en service, faux sinon
# - void assign_craft(const Aircraft& aircraft) : assigne un avion au terminal
# - void start_service(const Aircraft& aircraft) : commence le service du terminal
# - void finish_service() : met un terme au service du terminal
# - void move() override : si le terminal contient un avion et est en service, alors on incrémente la valeur de "service_progress" qui sert de timer au service du terminal

# Tower utilise la classe Airport en en prenant un dans son constructeur, Tower utilise également Aircraft pour ses deux fonctions publiques get_instructions et arrived_at_terminal.
# Aicraft utilise la classe Tower en l'assignant avec son constructeur.
# Airport possède un champs Tower, qui sera retourné dans la fonction get_tower, utilise la classe Terminal en l'utilisant pour créer un champs qui sera une liste de Terminal et pour retourner un Terminal avec get_terminal. Enfin Airport utilise la classe Aircraft dans la fonction reserve_terminal.
# Terminal possède un champs qui utilise la classe Aircraft, et ce champs est utilisé par plusieurs fonctions-membres.


Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?

# Les classes et fonctions qui sont impliquées dans la génération du chemin d'un avion sont la classe Tower avec get_instructions et la classe Aicraft avec la fonction move

Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
Expliquez les intérêts de ce choix.

# Le conteneur de la librairie standard qui a été choisi pour représenter le chemin est std::deque<Waypoint> car on peut accéder au début et à la fin du conteneur en ajoutant ou retirant du deque.


## C- Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.

# Les vitesses maximales et accélérations de chaque avion sont définies dans la classe aircraft_types avec max_air_speed et max_accel. 

Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.

# C'est dans la fonction init_aircraft_types qu'on attribue la vitesse et l'accéléation aux différents types d'avions, c'est donc sur la ligne  "aircraft_types[2] = new AircraftType { .02f, .05f, .02f, MediaPath { "concorde_af.png" } };" que j'ai changé les vitesses et accélérations en "aircraft_types[2] = new AircraftType { .02f, .10f, .04f, MediaPath { "concorde_af.png" } };"

2) Identifiez quelle variable contrôle le framerate de la simulation.\
Le framerate correspond au temps de rafraichissement du programme, c'est-à-dire le nombre de fois où les éléments du programme seront mis à jour (ajout de nouvel avion à la simulation, déplacement, etc) en une seconde.\

# La variable ticks_per_sec dans le fichier opengl_interface.hpp est celle qui contrôle le framerate de la simulation.

Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.

# J'ai ajouté 2 lignes dans la fonction create_keystrokes qui augmente ou diminiue le framerate si on appuie sur l ou m.

Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?\

# Si je mets le framerate à 0, le programme s'arrête.

Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.

# Je crée une nouvelle variable boolean pause dans opengl_interface.hpp que je vais utiliser dans le la fonction timer() de opengl_interface.cpp pour arrêter les mouvements des items du programme si pause est True. On change la valeur de pause avec la touche p.

3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.

# C'est la variable SERVICE_CYCLES qui contrôle le temps de débarquement des avions.

4) Lorsqu'un avion a décollé, il réattérit peu de temps après.
Assurez-vous qu'à la place, il soit supprimé de la `move_queue`.\
Pour tester, il suffit de dézoomer et de vérifier que les avions suffisament éloignés ne bougent plus.
Indices :\
A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\
Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?
A quel endroit de la callstack pourriez-vous le faire à la place ?\
Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?

# Il suffit de rajouter un champs booléen has_landed dans la classe Aicraft qui nous dira si l'avion a déjà atterri. Si c'est le cas, alors la fonction timer regardera le rendu de la fonction move() de Aircraft (qui est bool et plus void), si c'est true, alors on laisse l'avion dans la move_queue, on le retire sinon. La fonction move de Aircraft va renvoyer faux si l'avion n'a plus de chemin (sa liste de Waypoint est vide) et que il a déjà atterri. Le champs has_landed est modifé dans la fonction get_instructions() de Tower, lorsque l'avion redécolle.

5) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
Il faut également penser à le supprimer de cette liste avant de le détruire.
Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.\
Essayez maintenant de supprimer complètement l'avion du programme lorsque vous le retirez de la `move_queue`.\
En dézoomant, vous devriez maintenant constater que les avions disparaissent maintenant de l'écran.

# Il suffit d'autorise le constructeur et le destructeur de Displayable à ajouter ou effacer des éléments de la display_queue.

6) La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

# On peut à présent utiliser une map qui aura comme clé un Aicraft et comme valeur l'indice du terminal associé.

## D- Théorie

1) Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?

# La classe Tower peut réserver un terminal de l'aéroport en créant une map reserved_terminals qui prendra un Aicraft et un size_t qui est le numéro du terminal.

2) En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passer par une réference constante ?

# Dans la fonction turn, la direction est amenée à être modifiée donc on ne veut pas que cela impacte la direction passée en paramètre

Pourquoi n'est-il pas possible d'éviter la copie du `Point3D` passé en paramètre ?

# Car la direction n'est pas passée en référence, donc il faut que la fonction copie la direction si elle veut la modifier, si modification il y a.

## E- Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme.
La fonction move() n'utilise pas le vrai temps. Faites en sorte que si.
Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop).
Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames.
Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate.
Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction `move` des `DynamicObject`, et utilisez-la pour calculer les nouvelles positions de chaque avion.
Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.
