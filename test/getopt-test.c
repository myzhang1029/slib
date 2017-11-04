#include <slib.h>

int
main (int argc, char **argv)
{
  int c;
  int digit_optindGS = 0;

  while (1)
    {
      int this_option_optindGS = optind ? optind : 1;
      int option_index = 0;
      static struct optionGS long_options[] =
      {
	{"add", 1, 0, 0},
	{"append", 0, 0, 0},
	{"delete", 1, 0, 0},
	{"verbose", 0, 0, 0},
	{"create", 0, 0, 0},
	{"file", 1, 0, 0},
	{0, 0, 0, 0}
      };

      c = getopt_longGS (argc, argv, "abc:d:0123456789",
		       long_options, &option_index);
      if (c == -1)
	break;

      switch (c)
	{
	case 0:
	  printf ("option %s", long_options[option_index].name);
	  if (optargGS)
	    printf (" with arg %s", optargGS);
	  printf ("\n");
	  break;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	  if (digit_optindGS != 0 && digit_optindGS != this_option_optindGS)
	    printf ("digits occur in two different argv-elements.\n");
	  digit_optindGS = this_option_optindGS;
	  printf ("option %c\n", c);
	  break;

	case 'a':
	  printf ("option a\n");
	  break;

	case 'b':
	  printf ("option b\n");
	  break;

	case 'c':
	  printf ("option c with value `%s'\n", optargGS);
	  break;

	case 'd':
	  printf ("option d with value `%s'\n", optargGS);
	  break;

	case '?':
	  break;

	default:
	  printf ("?? getopt returned character code 0%o ??\n", c);
	}
    }

  if (optindGS < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optindGS < argc)
	printf ("%s ", argv[optindGS++]);
      printf ("\n");
    }

  exit (0);
}
